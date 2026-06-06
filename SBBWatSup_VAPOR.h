#pragma once 

#ifndef SBBWatSup_VAPOR_CF_h
#define SBBWatSup_VAPOR_CF_h

#include "MrImagingFW/libSBBFW/SeqBuildBlock.h"
#include "MrMeasSrv/SeqIF/libRT/sFREQ_PHASE.h"
#include "MrMeasSrv/SeqIF/libRT/sGRAD_PULSE.h"
#include "MrMeasSrv/SeqIF/libRT/sRF_PULSE.h"
#include "MrProtSrv/Domain/CoreNative/SeqLim.h"
#include "MrProtSrv/Domain/MrProtData/MrProt/MrProt.h"
#include "MrProtSrv/Domain/MrProtData/MrProt/SeqIF/SeqExpo.h"
#include "MrImagingFW/WIPParameterTool/WIPParameterTool.h"
#include "MrProtSrv/Domain/CoreNative/MrWipMemBlock.h"
#include "MrMeasSrv/SeqIF/libRT/sROT_MATRIX.h"
#include "MrProtSrv/Domain/CoreNative/MrSpectroscopy.h"
#include "MrMeasSrv/MeasPatient/MeasPatient.h"
// #include "MrSpecAcq/XA60_RosetteSpinEcho_VAPOR/csi_fid.h"

#include "MrSpecAcq/libSpecSBB/SBBWatSup.h" // Inherited from SBBWatSup.h
// #include "MrSpecAcq/libSpecSBB/SBBWatSup_VAPOR.cpp"


#ifdef BUILD_VAPOR_SBB
#define __OWNER
#endif
#include "MrGlobalDefinitions/ImpExpCtrl.h"

#include <type_traits>

class MrProt;
class SeqLim;
namespace MrProtocolData { class SeqExpo; }
class sSLICE_POS;
class SBBList;
namespace WPT_NAMESPACE { class WIPParameterTool; }

// #ifdef SEQ_NAMESPACE
// #error SEQ_NAMESPACE not defined
// #endif

//namespace CSI_FID {
// #endif


class /*__IMP_EXP*/ SeqBuildBlockWatSupVAPOR_CF : public SeqBuildBlockWatSup
{
    // static_assert(std::is_base_of<SeqBuildBlockWatSup, SeqBuildBlockWatSupVAPOR_CF>::value,
    //     "Not actually deriving from SeqBuildBlockWatSup");
    public: 
        //SeqBuildBlockWatSupVAPOR_CF(SBBList* pSBBList)
        //: SeqBuildBlock(pSBBList)
        //{
        //    setIdent("SBBWatSup_VAPOR_CF");
        // }
        // SeqBuildBlockWatSupVAPOR_CF();
        SeqBuildBlockWatSupVAPOR_CF(/*SBBList* pSBBList*/);
        

        // static_assert(std::is_base_of<SeqBuildBlockWatSup, SeqBuildBlockWatSupVAPOR_CF>::value,
        //     "Not actually deriving from SeqBuildBlockWatSup");
    
        virtual ~SeqBuildBlockWatSupVAPOR_CF() = default;

        SeqBuildBlockWatSupVAPOR_CF(const SeqBuildBlockWatSupVAPOR_CF& right) = delete;
        SeqBuildBlockWatSupVAPOR_CF& operator=(const SeqBuildBlockWatSupVAPOR_CF& right) = delete;
        SeqBuildBlockWatSupVAPOR_CF(SeqBuildBlockWatSupVAPOR_CF&& right) = delete;
        SeqBuildBlockWatSupVAPOR_CF& operator=(SeqBuildBlockWatSupVAPOR_CF&& right) = delete;

        // void setWipTool(const WPT_NAMESPACE::WIPParameterTool* p) { m_pWip = p; }

        // bool initialize(SeqLim& rSeqLim) override;

        //!    Prepares the SBB functions for run. Returns true, if successful.
        bool prep(MrProt& rMrProt, SeqLim& rSeqLim, MrProtocolData::SeqExpo& rSeqExpo) override;
        // In cpp, call SeqBuildBlokWatSup :: prep() first, then define your extra RFs and Gradients

        //!    Executes the real time part of the SBB. Returns true, if successful.
        bool run(MrProt& rMrProt, SeqLim& rSeqLim, MrProtocolData::SeqExpo& rSeqExpo, sSLICE_POS*) override;

        void setRf_exc(sRF_PULSE_EXT* sRF_PULSE_EXTVal);
        void setGrad_exc(sGRAD_PULSE* sGRAD_PULSE_EXTVal );
        void setSlicePosFov(sSLICE_POS* sSLICE_POSVal);

    protected:
        char m_asym_sinc[32];
        sRF_PULSE_EXT m_vap_asym1{"ss_vap_asym1"};

        sFREQ_PHASE m_ph_s_asym1{"ss_ph_s_asym1"};
        sFREQ_PHASE m_ph_n_asym1{"ss_ph_n_asym1"};

        sRF_PULSE_EXT m_vap_asym2{"ss_vap_asym2"};

        sFREQ_PHASE m_ph_s_asym2{"ss_ph_s_asym2"};
        sFREQ_PHASE m_ph_n_asym2{"ss_ph_n_asym2"};

        sRF_PULSE_EXT m_vap_asym3{"ss_vap_asym3"};

        sFREQ_PHASE m_ph_s_asym3{"ss_ph_s_asym3"};
        sFREQ_PHASE m_ph_n_asym3{"ss_ph_n_asym3"};

        sRF_PULSE_EXT m_vap_asym4{"ss_vap_asym4"};

        sFREQ_PHASE m_ph_s_asym4{"ss_ph_s_asym4"};
        sFREQ_PHASE m_ph_n_asym4{"ss_ph_n_asym4"};

        sRF_PULSE_EXT m_vap_asym5{"ss_vap_asym5"};

        sFREQ_PHASE m_ph_s_asym5{"ss_ph_s_asym5"};
        sFREQ_PHASE m_ph_n_asym5{"ss_ph_n_asym5"};

        sRF_PULSE_EXT m_vap_asym6{"ss_vap_asym6"};

        sFREQ_PHASE m_ph_s_asym6{"ss_ph_s_asym6"};
        sFREQ_PHASE m_ph_n_asym6{"ss_ph_n_asym6"};

        sRF_PULSE_EXT m_vap_asym7{"ss_vap_asym7"};

        sFREQ_PHASE m_ph_s_asym7{"ss_ph_s_asym7"};
        sFREQ_PHASE m_ph_n_asym7{"ss_ph_n_asym7"};

        sRF_PULSE_EXT m_vap_asym8{"ss_vap_asym8"};

        sFREQ_PHASE m_ph_s_asym8{"ss_ph_s_asym8"};
        sFREQ_PHASE m_ph_n_asym8{"ss_ph_n_asym8"};

        // CF VAPOR 

        sRF_PULSE_GAUSS m_rf_vapor1{"ss_rf_vapor1"};
        sRF_PULSE_GAUSS m_rf_vapor2{"ss_rf_vapor2"};
        sRF_PULSE_GAUSS m_rf_vapor3{"ss_rf_vapor3"};
        sRF_PULSE_GAUSS m_rf_vapor4{"ss_rf_vapor4"};
        sRF_PULSE_GAUSS m_rf_vapor5{"ss_rf_vapor5"};
        sRF_PULSE_GAUSS m_rf_vapor6{"ss_rf_vapor6"};
        sRF_PULSE_GAUSS m_rf_vapor7{"ss_rf_vapor7"};
        sRF_PULSE_GAUSS m_rf_vapor8{"ss_rf_vapor8"};

        sFREQ_PHASE m_ph_s_vapor1{"ss_ph_s_vapor1"};
        sFREQ_PHASE m_ph_n_vapor1{"ss_ph_n_vapor1"};
        sFREQ_PHASE m_ph_s_vapor2{"ss_ph_s_vapor2"};
        sFREQ_PHASE m_ph_n_vapor2{"ss_ph_n_vapor2"};
        sFREQ_PHASE m_ph_s_vapor3{"ss_ph_s_vapor3"};
        sFREQ_PHASE m_ph_n_vapor3{"ss_ph_n_vapor3"};
        sFREQ_PHASE m_ph_s_vapor4{"ss_ph_s_vapor4"};
        sFREQ_PHASE m_ph_n_vapor4{"ss_ph_n_vapor4"};
        sFREQ_PHASE m_ph_s_vapor5{"ss_ph_s_vapor5"};
        sFREQ_PHASE m_ph_n_vapor5{"ss_ph_n_vapor5"};
        sFREQ_PHASE m_ph_s_vapor6{"ss_ph_s_vapor6"};
        sFREQ_PHASE m_ph_n_vapor6{"ss_ph_n_vapor6"};
        sFREQ_PHASE m_ph_s_vapor7{"ss_ph_s_vapor7"};
        sFREQ_PHASE m_ph_n_vapor7{"ss_ph_n_vapor7"};
        sFREQ_PHASE m_ph_s_vapor8{"ss_ph_s_vapor8"};
        sFREQ_PHASE m_ph_n_vapor8{"ss_ph_n_vapor8"};


        // CF FAST

        sRF_PULSE_GAUSS m_rf_fast1{"ss_rf_fast1"};
        sRF_PULSE_GAUSS m_rf_fast2{"ss_rf_fast2"};
        sRF_PULSE_GAUSS m_rf_fast3{"ss_rf_fast3"};
        sRF_PULSE_GAUSS m_rf_fast4{"ss_rf_fast4"};
        sRF_PULSE_GAUSS m_rf_fast5{"ss_rf_fast5"};

        sFREQ_PHASE m_ph_s_fast1{"ss_ph_s_fast1"};
        sFREQ_PHASE m_ph_n_fast1{"ss_ph_n_fast1"};
        sFREQ_PHASE m_ph_s_fast2{"ss_ph_s_fast2"};
        sFREQ_PHASE m_ph_n_fast2{"ss_ph_n_fast2"};
        sFREQ_PHASE m_ph_s_fast3{"ss_ph_s_fast3"};
        sFREQ_PHASE m_ph_n_fast3{"ss_ph_n_fast3"};
        sFREQ_PHASE m_ph_s_fast4{"ss_ph_s_fast4"};
        sFREQ_PHASE m_ph_n_fast4{"ss_ph_n_fast4"};
        sFREQ_PHASE m_ph_s_fast5{"ss_ph_s_fast5"};
        sFREQ_PHASE m_ph_n_fast5{"ss_ph_n_fast5"};

        // CF HGWS

        char m_HG[32];
        sRF_PULSE_EXT m_HG1{"ss_HG1"};

        sFREQ_PHASE m_ph_s_HG1{"ss_ph_s_HG1"};
        sFREQ_PHASE m_ph_n_HG1{"ss_ph_n_HG1"};

        sRF_PULSE_EXT m_HG2{"ss_HG2"};

        sFREQ_PHASE m_ph_s_HG2{"ss_ph_s_HG2"};
        sFREQ_PHASE m_ph_n_HG2{"ss_ph_n_HG2"};

        sRF_PULSE_EXT m_HG3{"ss_HG3"};

        sFREQ_PHASE m_ph_s_HG3{"ss_ph_s_HG3"};
        sFREQ_PHASE m_ph_n_HG3{"ss_ph_n_HG3"};

        sRF_PULSE_EXT m_HG4{"ss_HG4"};

        sFREQ_PHASE m_ph_s_HG4{"ss_ph_s_HG4"};
        sFREQ_PHASE m_ph_n_HG4{"ss_ph_n_HG4"};

        sRF_PULSE_EXT m_HG5{"ss_HG5"};

        sFREQ_PHASE m_ph_s_HG5{"ss_ph_s_HG5"};
        sFREQ_PHASE m_ph_n_HG5{"ss_ph_n_HG5"};   
        
        // gradients

        // VAPOR CF

        sGRAD_PULSE m_vaporsp_1{"ss_vaporsp_1"};
        sGRAD_PULSE m_vaporsp_2{"ss_vaporsp_2"};
        sGRAD_PULSE m_vaporsp_3{"ss_vaporsp_3"};
        sGRAD_PULSE m_vaporsp_4{"ss_vaporsp_4"};
        sGRAD_PULSE m_vaporsp_5{"ss_vaporsp_5"};
        sGRAD_PULSE m_vaporsp_6{"ss_vaporsp_6"};
        sGRAD_PULSE m_vaporsp_7{"ss_vaporsp_7"};
        sGRAD_PULSE m_vaporsp_8{"ss_vaporsp_8"};

        // CF FAST

        sGRAD_PULSE m_fastsp_1{"ss_fastsp_1"};
        sGRAD_PULSE m_fastsp_2{"ss_fastsp_2"};
        sGRAD_PULSE m_fastsp_3{"ss_fastsp_3"};
        sGRAD_PULSE m_fastsp_4{"ss_fastsp_4"};
        sGRAD_PULSE m_fastsp_5{"ss_fastsp_5"};

        // CF HGWS

        sGRAD_PULSE m_HGsp_1{"ss_HGsp_1"};
        sGRAD_PULSE m_HGsp_2{"ss_HGsp_2"};
        sGRAD_PULSE m_HGsp_3{"ss_HGsp_3"};
        sGRAD_PULSE m_HGsp_4{"ss_HGsp_4"};
        sGRAD_PULSE m_HGsp_5{"ss_HGsp_5"};

        // CF WET
        sRF_PULSE_GAUSS m_rf_ws1{"ss_rf_ws1"};
        sRF_PULSE_GAUSS m_rf_ws2{"ss_rf_ws2"};
        sRF_PULSE_GAUSS m_rf_ws3{"ss_rf_ws3"};

        sFREQ_PHASE m_ph_s_ws{"ss_ph_s_ws"};
        sFREQ_PHASE m_ph_n_ws{"ss_ph_n_ws"};


        sGRAD_PULSE m_wssp_ph; // water suppression spoiler - phase
        sGRAD_PULSE m_wssp_ro; // water suppression spoiler - readout
        sGRAD_PULSE m_wssp_sl; // water suppression spoiler - slice

        sGRAD_PULSE m_finsp_sl; // final spoiler - slice
        sGRAD_PULSE m_finsp_ro; // final spoiler - readout
        sGRAD_PULSE m_finsp_ph; // final spoiler - phase

        // // SBB for CHESS/WET
        // SeqBuildBlockWatSup m_sWaterSat{nullptr};

        sRF_PULSE_EXT* m_rf_exc{nullptr};
        sGRAD_PULSE* m_grad_exc{nullptr};
        sSLICE_POS* m_fov{nullptr};

    private:
    // add the variables here

        const WPT_NAMESPACE::WIPParameterTool* m_pWip{nullptr};
        sROT_MATRIX m_RotMatrix;

        long m_vaporsp_1amp{0};
        long m_vaporsp_2amp{0};
        long m_vaporsp_3amp{0};
        long m_vaporsp_4amp{0};
        long m_vaporsp_5amp{0};
        long m_vaporsp_6amp{0};
        long m_vaporsp_7amp{0};
        long m_vaporsp_8amp_1{0};
        long m_vaporsp_8amp_2{0};
        long m_vapSpRamp{0}; 
        long m_vaporsp_dur{0};

        long m_HGsp_dur{0};
        long m_HGsp_1_3amp{0};
        long m_HGsp_4amp{0};
        long m_HGsp_5amp{0};
        long m_HGSpRamp{0};

        long m_fastsp_1_3amp{0}; 
        long m_fastsp_4amp{0};
        long m_fastsp_5amp{0}; 
        long m_fastSpRamp{0}; 
        long m_fastsp_dur_1_3{0};
        long m_fastsp_dur_4{0};
        long m_fastsp_dur_5{0};
        double FASTgradmoment_1_3{0};
        double FASTgradmoment_4{0};
        double FASTgradmoment_5{0};
        long FASTpulsedur_1_4{0};
        long FASTpulsedur_5{0};

        long t1{0};
        long t2{0};
        long t3{0};
        long t4{0};
        long t5{0};
        long t6{0};
        long t7{0};
        long t8{0};
        long fast_t1_3{0};
        long fast_t4{0};
        long fast_t5{0};
        long HG_t1{0};
        long HG_t2{0};
        long HG_t3{0}; 
        long HG_t4{0};
        long HG_t5{0};
        long deadtime_1{0};
        long deadtime_2{0};
        long deadtime_3{0};
        long deadtime_4{0};
        long deadtime_5{0};
        long deadtime_6{0};
        long deadtime_7{0};
        long deadtime_8{0};
        long HG_deadtime_1{0};
        long HG_deadtime_2{0};
        long HG_deadtime_3{0};
        long HG_deadtime_4{0};
        long HG_deadtime_5{0};

        bool m_bvap{true};
        double WStechnique{0};
        double asym_factor{0};
        long beta_vapor{0};
        long grad_strength{0};
        double beta_multiplier_1{0};
        double beta_multiplier_2{0};
        double beta_multiplier_3{0};
        double beta_multiplier_4{0};
        double beta_multiplier_5{0};
        double beta_multiplier_6{0};
        double beta_multiplier_7{0};
        double beta_multiplier_8{0};
        long WS_option{0};
        long VAPOR_RF_dur{0};
        long freq_shift{0};
        long   VAPOR_bw {0};
        long   asym_dur{0};
        double offset_asymWS{0};
        double offset_HGWS{0};
        long m_lis_watsup{0};
        long m_lis_watsupRF{0};
        long m_lexcit_delay{0};
        long lT{0};

        long tau{0};
        long tau3{0};
        long l{0};
        long d{0};
        long wsspgradmoment{0};
        long ramptime {0};
        // static const int32_t GRAD_RASTER_TIME{0};        


// } 

};

inline void SeqBuildBlockWatSupVAPOR_CF::setRf_exc(sRF_PULSE_EXT* sRF_PULSE_EXTVal)
{
    m_rf_exc = sRF_PULSE_EXTVal;
}

inline void SeqBuildBlockWatSupVAPOR_CF::setGrad_exc(sGRAD_PULSE* sGRAD_PULSE_EXTVal)
{
    m_grad_exc = sGRAD_PULSE_EXTVal;
}

inline void SeqBuildBlockWatSupVAPOR_CF::setSlicePosFov(sSLICE_POS* sSLICE_POSVal)
{
    m_fov = sSLICE_POSVal;
}

// static_assert(std::is_base_of<::SeqBuildBlockWatSup, SeqBuildBlockWatSupVAPOR_CF>::value,
//     "Not actually deriving from SeqBuildBlockWatSup");

// #ifdef SEQ_NAMESPACE
//} // namespace SEQ_NAMESPACE
// #endif


#endif