#include <iostream>
#include <iomanip>
#include <memory>
#include <thread>

#include <libcamera/libcamera.h>
#include <opencv2/opencv.hpp>

using namespace libcamera;
using namespace std::chrono_literals;

static std::shared_ptr<Camera> camera;

static void requestComplete(Request *request)
{
    if (request->status() == Request::RequestCancelled) return;

    const std::map<const Stream *, FrameBuffer *> &buffers = request->buffers();

    for (auto bufferPair : buffers) {
        FrameBuffer *buffer = bufferPair.second;
        const FrameMetadata &metadata = buffer->metadata();
        std::cout << " seq: " << std::setw(6) << std::setfill('0') << metadata.sequence << " bytesused: ";

        unsigned int nplane = 0;
        for (const FrameMetadata::Plane &plane : metadata.planes())
        {
            std::cout << plane.bytesused;
            if (++nplane < metadata.planes().size()) std::cout << "/";
        }

        std::cout << std::endl;
    }


}

int main() {
    std::unique_ptr<CameraManager> cameraManager = std::make_unique<CameraManager>();
    cameraManager->start();

    auto cameras = cameraManager->cameras();

    if (cameras.empty()) {
        std::printf("No cameras found.\n");
        return 1;
    }
    
    std::string cameraId = cameras[0]->id();

    auto camera = cameraManager->get(cameraId);

    if (!camera) {
        std::printf("Camera %s not found.\n", cameraId.c_str());
        return 1;
    }

    camera->acquire();

    std::unique_ptr<CameraConfiguration> config = camera->generateConfiguration( { StreamRole::Viewfinder } );

    if (!config) {
        std::printf("Could not configure camera %s.\n", cameraId.c_str());
        return 1;
    }

    StreamConfiguration &streamCfg = config->at(0);
    std::printf("Stream configuration: \n", streamCfg.toString().c_str());
    
    streamCfg.size.width = 640;
    streamCfg.size.height = 480;

    config->validate();

    std::cout << "Validated viewfinder configuration is: " << streamCfg.toString() << std::endl;

    camera->configure(config.get());

    FrameBufferAllocator *allocator = new FrameBufferAllocator(camera);

    for (StreamConfiguration &cfg : *config) {
        int ret = allocator->allocate(cfg.stream());
        if (ret < 0) {
            std::cerr << "Can't allocate buffers" << std::endl;
            return -ENOMEM;
        }

        size_t allocated = allocator->buffers(cfg.stream()).size();
        std::cout << "Allocated " << allocated << " buffers for stream" << std::endl;
    }

    Stream *stream = streamCfg.stream();
    const std::vector<std::unique_ptr<FrameBuffer>> &buffers = allocator->buffers(stream);
    std::vector<std::unique_ptr<Request>> requests;

    for (unsigned int i = 0; i < buffers.size(); ++i) {
        std::unique_ptr<Request> request = camera->createRequest();
        if (!request)
        {
            std::cerr << "Can't create request" << std::endl;
            return -ENOMEM;
        }

        const std::unique_ptr<FrameBuffer> &buffer = buffers[i];
        int ret = request->addBuffer(stream, buffer.get());
        if (ret < 0)
        {
            std::cerr << "Can't set buffer for request"
                << std::endl;
            return ret;
        }

        requests.push_back(std::move(request));
    }

    camera->requestCompleted.connect(requestComplete);

    return 0;
}