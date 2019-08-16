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
        void handleInvalidConnection(uint8_t processNumber);

    private:
        void initializeHMMessageQueue();
        void initializeMainMessageQueue();
        void initializeChannels();

        void lostConnection(config::UICommunicationMode mode, std::string systemMode);

        config::UIMessageQueues uiMessageQueuesParameters_;
        std::shared_ptr<communication::MessageQueueWrapper> hmMessageQueue_;
        std::shared_ptr<communication::MessageQueueWrapper> mainMessageQueue_;

        utility::Logger& logger_;

        uint8_t firstNetCounter_;
        std::vector<uint8_t> firstNetChannels_;
        uint8_t secondNetCounter_;
        std::vector<uint8_t> secondNetChannels_;

        const std::string CHANGE_WLAN_1 = "wlan1 g";
        const std::string CHANGE_WLAN_2 = "wlan2 a";

        const std::string INIT_FIRST_NET = "../../scripts/init_MASTER_NET.sh";
        const std::string INIT_SECOND_NET = "../../scripts/init_REDUNDANT_NET.sh";

        const std::string CHANGE_NET = "../../scripts/change_net.sh";
    };
}

#endif // HM_H
