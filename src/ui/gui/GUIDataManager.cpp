#include "GUIDataManager.h"

using namespace gui;
using namespace std;
using namespace communication;

GUIDataManager::GUIDataManager()
    : mainBitsInformation_({0}),
      isAHRSActive_(false),
      areBITSActive_(false),
      planeName_("")
{}

void GUIDataManager::setMainBitsInformation(const BitsInformation& bitsInformation) noexcept
{
    mainBitsInformation_ = bitsInformation;
}

const BitsInformation& GUIDataManager::getMainBitsInformation() const noexcept
{
    return mainBitsInformation_;
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

void GUIDataManager::setSystemActivation() noexcept
{
    isAHRSActive_ = true;
}

bool GUIDataManager::isSystemAcitve() noexcept
{
    return isAHRSActive_;
}

void GUIDataManager::setBITSActivation() noexcept
{
    areBITSActive_ = true;
}

bool GUIDataManager::areBITSActive() noexcept
{
    return areBITSActive_;
}

bool GUIDataManager::getIsMasterCalibrated() const
{
    return isMasterCalibrated_;
}

void GUIDataManager::setIsMasterCalibrated(bool isMasterCalibrated)
{
    isMasterCalibrated_ = isMasterCalibrated;
}

communication::BitsInformation GUIDataManager::getRedundantBitsInformation() const
{
    return redundantBitsInformation_;
}

void GUIDataManager::setRedundantBitsInformation(const communication::BitsInformation &redundantBitsInformation)
{
    redundantBitsInformation_ = redundantBitsInformation;
}

void GUIDataManager::setMainCallibrationParameters(const communication::CalibrationConfiguration& paramteres) noexcept
{
    masterCallibrationConfiguration_ = paramteres;
}

void GUIDataManager::setRedundantCallibrationParameters(const communication::CalibrationConfiguration& paramteres) noexcept
{
    redundantCallibrationConfiguration_ = paramteres;
}

const communication::CalibrationConfiguration& GUIDataManager::getMainCallibrationParameters() const noexcept
{
    return masterCallibrationConfiguration_;
}

const communication::CalibrationConfiguration& GUIDataManager::getRedundantCallibrationParameters() const noexcept
{
    return redundantCallibrationConfiguration_;
}
