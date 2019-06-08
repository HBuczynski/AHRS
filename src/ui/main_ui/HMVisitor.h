#ifndef HMVISITOR_H
#define HMVISITOR_H

#include <interfaces/hm/HMCommandVisitor.h>
#include <logger/Logger.h>

namespace main_process
{
    class UIApplicationManager;

    class HMVisitor final : public communication::HMCommandVisitor
    {
    public:
        HMVisitor(UIApplicationManager *uiApplicationManager);
        ~HMVisitor();

        void visit(const communication::HMErrorCommand& command);

    private:
        UIApplicationManager* uiApplicationManager_;
        utility::Logger& logger_;
    };
}

#endif // HMVISITOR_H
