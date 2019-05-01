#ifndef GUIWIRELESSCOMWRAPPERCMMAND_H
#define GUIWIRELESSCOMWRAPPERCMMAND_H

#include "GUIResponse.h"

namespace communication
{
    class GUIWirelessComWrapperResponse : public GUIResponse
    {
    public:
        GUIWirelessComWrapperResponse(const std::vector<uint8_t> &data);
        ~GUIWirelessComWrapperResponse();

        virtual std::vector<uint8_t > getFrameBytes() override;
        virtual std::string getName() override;
        virtual void accept(GUIResponseVisitor& visitor) override;

        const std::vector<uint8_t>& getDataFrame() const;
        void setDataFrame(const std::vector<uint8_t>& data);
    private:
        virtual void initializeDataSize() override;

        std::vector<uint8_t> data_;
    };
}

#endif // GUIWIRELESSCOMWRAPPERCMMAND_H
