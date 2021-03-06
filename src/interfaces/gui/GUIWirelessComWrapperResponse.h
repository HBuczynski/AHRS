#ifndef GUIWIRELESSCOMWRAPPERCMMAND_H
#define GUIWIRELESSCOMWRAPPERCMMAND_H

#include "GUIResponse.h"
#include <config_reader/UIParameters.h>

namespace communication
{
    class GUIWirelessComWrapperResponse : public GUIResponse
    {
    public:
        GUIWirelessComWrapperResponse(config::UICommunicationMode mode, const std::vector<uint8_t> &data);
        ~GUIWirelessComWrapperResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

        const std::vector<uint8_t>& getDataFrame() const;
        void setDataFrame(const std::vector<uint8_t>& data);
        config::UICommunicationMode getMode() const;
        void setMode(const config::UICommunicationMode &mode);

    private:
        virtual void initializeDataSize() override;

        config::UICommunicationMode mode_;
        std::vector<uint8_t> data_;
    };
}

#endif // GUIWIRELESSCOMWRAPPERCMMAND_H
