#include "GUIDataManager.h"

using namespace gui;
using namespace std;

GUIDataManager::GUIDataManager()
    : bitsInformation_({0}),
      isAHRSActive_(false),
      planeName_("")
{}

void GUIDataManager::setBitsInformation(const BitsInformation& bitsInformation) noexcept
{
    bitsInformation_ = bitsInformation;
}

const BitsInformation& GUIDataManager::getBitsInformation() const noexcept
{
    return bitsInformation_;
}

void GUIDataManager::setPlaneName(const string& name) noexcept
{
    planeName_ = name;
}

const string& GUIDataManager::getPlaneName() const noexcept
{
    return planeName_;
}

void GUIDataManager::setPlaneDataset(const string& planeDataset) noexcept
{
    planeDataset_ = planeDataset;
}

const string &GUIDataManager::getPlaneDataset() const noexcept
{
    return planeDataset_;
}

void GUIDataManager::setSystemActivation()
{
    isAHRSActive_ = true;
}

bool GUIDataManager::isSystemAcitve()
{
    return isAHRSActive_;
}
