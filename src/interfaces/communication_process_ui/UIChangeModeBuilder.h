#ifndef AHRS_UICHANGESTATEBUILDER_H
#define AHRS_UICHANGESTATEBUILDER_H

#include <UICommandBuilder.h>

namespace communication
{
    class UIChangeModeBuilder final : public UICommandBuilder
    {
    public:
        UIChangeModeBuilder();
        ~UIChangeModeBuilder();

        std::unique_ptr<UICommand> create(const std::vector<uint8_t> &commandInBytes) override;

    private:
        const uint16_t INIT_DATA_POSITION_IN_FRAME = 6;
    };
}


#endif //AHRS_UICHANGESTATEBUILDER_H
