#ifndef FM_H
#define FM_H

#include <logger/Logger.h>
#include <config_reader/UIParameters.h>
#include <message_queue_wrapper/MessageQueueWrapper.h>
#include <interfaces/hm/HMErrorCommand.h>

namespace redundancy
{
    class FM
    {
    public:
        FM();

        void initialize();
        void handeError(const communication::HMErrorCommand& command);

    private:
        void initializeHMMessageQueue();
        void initializeMainMessageQueue();

        void lostConnection(config::UICommunicationMode mode);

        config::UIMessageQueues uiMessageQueuesParameters_;
        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> mainMessageQueue_;

        utility::Logger& logger_;
    };
}

#endif // HM_H
