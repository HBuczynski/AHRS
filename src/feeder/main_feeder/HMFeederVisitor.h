#ifndef HMFEEDERVISITOR_H
#define HMFEEDERVISITOR_H

#include <interfaces/hm/HMCommandVisitor.h>
#include <logger/Logger.h>

namespace main_process
{
    class ApplicationManager;

    class HMFeederVisitor final : public communication::HMCommandVisitor
    {
    public:
        HMFeederVisitor(main_process::ApplicationManager *applicationManager);
        ~HMFeederVisitor();

        void visit(const communication::HMErrorCommand& command);
        void visit(const communication::HMInvalidConnectionCommand& command);

    private:
        ApplicationManager* applicationManager_;
        utility::Logger& logger_;
    };
}


#endif // HMFEEDERVISITOR_H
