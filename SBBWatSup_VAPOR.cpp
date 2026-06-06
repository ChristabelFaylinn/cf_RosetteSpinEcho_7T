#define SEQ_NAMESPACE CSI_FID

#include "MrSpecAcq/libSpecSBB/SBBWatSup_VAPOR.h"
#include "MrImagingFW/WIPParameterTool/WIPParameterTool.h"

// #define __OWNER
#include "MrGlobalDefinitions/ImpExpCtrl.h"
// #include "MrSpecAcq/libSpecSBB/SBBWatSup.h"
#include "MrSpecAcq/SpecUtils/EGA/SpecUtils.h"
// #include "MrSpecAcq/XA60_RosetteSpinEcho_VAPOR/csi_fid.cpp"
#include "MrImaging/libSBB/libSBBmsg.h"      // for MRI_SBB_SBB_... errors codes
#include "MrImagingFW/libSeqUTIF/libsequt.h" // for mSEQTest
#include "MrImagingFW/libSeqUtilFW/SeqTrace.h"
#include "MrMeasSrv/SeqIF/libRT/libRT.h"  
#include "MrProtSrv/Domain/MrProtData/MrProt/MeasParameter/MrTXSpec.h"
#include "MrImagingFW/libSeqUtilFW/SeqTrace.h"

// #ifndef SEQ_NAMESPACE
// #error SEQ_NAMESPACE not defined
// #endif


// #ifdef CSI_FID
// namespace CSI_FID {
// #endif
// using namespace SEQ_NAMESPACE;

// Only calculating the VAPOR delays and prepping the stuff, input needs to be given in the actual sequence
// need to define... 
// CF need to define WEAK RF stuff here, m_lis_watsup, etc. 


SeqBuildBlockWatSupVAPOR_CF::SeqBuildBlockWatSupVAPOR_CF(/*SBBList* pSBBList*/) : SeqBuildBlockWatSup(nullptr)
{
    // SeqBuildBlockWatSup::SeqBuildBlockWatSup(nullptr);
    setIdent("SBBWatSup_VAPOR_CF");
}

// SeqBuildBlockWatSupVAPOR_CF::SeqBuildBlockWatSupVAPOR_CF(SBBList* pSBBList) : SeqBuildBlock(pSBBList) 
// {
//     setIdent("SBBWatSup_VAPOR_CF");
// }


// if WIP UI is added here then it will own the special sequence card. so this will be called in the actual sequence

// Read inputs and calculate shapes and stuff


bool /*SEQ_NAMESPACE::*/SeqBuildBlockWatSupVAPOR_CF::prep (MrProt &rMrProt, SeqLim & rSeqLim, MrProtocolData::SeqExpo &rSeqExpo) // add wip param here maybe
{
    rSeqLim.setExtSrfFilename("%MEASCONST%/extrf/extrf_spec.dat");
    //setNLSStatus(MRI_SBB_SBB_NORMAL, "fSBBWatSupVAPORprep:", nullptr);
    // resetPrepared();
    SEQ_TRACE_WARN.print("SBB1");
    // if (!SeqBuildBlockWatSup::prep(rMrProt, rSeqLim, rSeqExpo))
    //     return false;

    // NLSStatus st = SeqBuildBlockWatSup::prepare(rMrProt, rSeqLim, rSeqExpo);
    // if (st != SEQU__NORMAL) return st;

    // const WPT_NAMESPACE::WIPParameterTool* wip = m_pWip;

    // // can delete this i think CF
    // WPT_NAMESPACE::WIPParameterTool tmp(rMrProt);
    // if (!wip) wip = &tmp;
    // ... 
    const MeasNucleus  mainNucleus(rMrProt.getsTXSPEC().getasNucleusInfo()[0].gettNucleus().c_str());
    // const double dLarmorConst = mainNucleus.getLarmorConst();
    const MeasNucleus  txNucleus(rMrProt.getsTXSPEC().getasNucleusInfo()[1].gettNucleus().c_str());

    // take the inputs from the special sequence card
 
    // beta_vapor = rMrProt.Mr?WipMemBlock().alFree[1];
    // beta_vapor = rMrProt.getLongValue

	// if (!wip.prepare (rMrProt, rSeqLim)) return MRI_SEQ_SEQU_ERROR;
	// if (!wip.prepare (rMrProt, rSeqLim)) return MRI_SEQ_SEQU_ERROR;

    beta_multiplier_1 = rMrProt.wipMemBlock().getadFree()[0];
    beta_multiplier_2 = rMrProt.wipMemBlock().getadFree()[1];
    beta_multiplier_3 = rMrProt.wipMemBlock().getadFree()[2];
    beta_multiplier_4 = rMrProt.wipMemBlock().getadFree()[3];
    beta_multiplier_5 = rMrProt.wipMemBlock().getadFree()[4];
    beta_multiplier_6 = rMrProt.wipMemBlock().getadFree()[5];
    beta_multiplier_7 = rMrProt.wipMemBlock().getadFree()[6];
    beta_multiplier_8 = rMrProt.wipMemBlock().getadFree()[7];
    t1 = rMrProt.wipMemBlock().getalFree()[8];
    t2 = rMrProt.wipMemBlock().getalFree()[9];
    t3 = rMrProt.wipMemBlock().getalFree()[10];
    t4 = rMrProt.wipMemBlock().getalFree()[11];
    t5 = rMrProt.wipMemBlock().getalFree()[12];
    t6 = rMrProt.wipMemBlock().getalFree()[13];
    t7 = rMrProt.wipMemBlock().getalFree()[14];
    t8 = rMrProt.wipMemBlock().getalFree()[15];
    beta_vapor = rMrProt.wipMemBlock().getalFree()[16];
    grad_strength = rMrProt.wipMemBlock().getalFree()[17];
    VAPOR_RF_dur = rMrProt.wipMemBlock().getalFree()[18];
    WS_option = rMrProt.wipMemBlock().getalFree()[19];
    freq_shift        = rMrProt.wipMemBlock().getalFree()[20]; 
    VAPOR_bw          = rMrProt.wipMemBlock().getalFree()[21]; 
    
    WStechnique = WS_option;

    SEQ_TRACE_WARN.print("%d",WS_option);

    // m_lSBBDurationPerRequest_us = grad_strength;
    // std::cout<<"beta_vapor: "<< beta_vapor<<std::endl;

    // SEQ_TRACE_WARN.print("SBB4");

	fast_t1_3 = 15000;
	fast_t4 = 17000;
	fast_t5 = 14000;

	std::cout<<"t1_1: "<< t1<<std::endl;
	// std::cout<<"m_bvap_1: "<< m_bvap<<std::endl;
	std::cout<<"beta_vapor: "<< beta_vapor<<std::endl;
	std::cout<<"multiplier: "<<beta_multiplier_8*beta_vapor<<std::endl;
	// std::cout<<"option: "<< WStechnique<<std::endl;
	
	//std::cout<<"multiplier: "<< beta_multiplier_5<<std::endl;

    // // VAPOR values 

	m_vapSpRamp = 200; // CF ramp duration? 
	m_vaporsp_1amp = grad_strength;
	m_vaporsp_2amp = grad_strength;
	m_vaporsp_3amp = grad_strength;
	m_vaporsp_4amp = grad_strength;
	m_vaporsp_5amp = grad_strength; // these values depends on RFs
	m_vaporsp_6amp = grad_strength;
	m_vaporsp_7amp = grad_strength;
	m_vaporsp_8amp_1 = grad_strength;
	m_vaporsp_8amp_2 = grad_strength;

	m_vaporsp_dur = 10000; // in us

	// FAST values 
	
	m_fastSpRamp = 200;
	

	// HGWS values

	m_HGsp_dur = 3000; 
	m_HGSpRamp = 200;
	m_HGsp_1_3amp = 10;
	m_HGsp_4amp = 9;
	m_HGsp_5amp = 8;

    // CF FAST 
	FASTgradmoment_1_3 = 168.;
	FASTgradmoment_4 = 235.;
	FASTgradmoment_5 = 235.;

	if( WStechnique == 3 ){
		strcpy( m_asym_sinc, "asym_400" ); // CF for VAPOR
	}
    else if (WStechnique == 4 || WStechnique == 5 || WStechnique == 9 || WStechnique == 10)
    {
		strcpy( m_asym_sinc, "asym_ex.jn_asym_ex_400"); // CF for VAPOR - JN_sinc
	}
	//else if(WStechnique == 5){
	//	strcpy( m_asym_sinc, "asym_ex.jn_asym_ex_400_rev"); // CF for VAPOR - reversed JN_sinc
	//}
	else if(WStechnique == 6){
		strcpy( m_asym_sinc, "asym_ex.asym_jn_4lobe_400"); // CF for VAPOR - truncated 4 lobe JN_sinc
	}
	else if(WStechnique == 7){
		strcpy( m_HG, "hg_ws_1_flipped"); // CF for VAPOR - Hypergeometric pulse
	}


    SEQ_TRACE_WARN.print("%s",m_HG);
	
    FASTpulsedur_1_4 = 6400.; // in us CF FAST
    FASTpulsedur_5 = 3700.; // in us CF FAST

    if (WStechnique == 4 || WStechnique == 9 || WStechnique == 10){
        // freq_shift = freq_shift; // in Hz; already set in WIP parameter CF
        offset_asymWS = freq_shift * VAPOR_RF_dur * (360. / (2*1000000));
    }
    else if (WStechnique == 5) {
        freq_shift = 15; // in Hz
        offset_asymWS = freq_shift * VAPOR_RF_dur * (360. / (2 * 1000000));
    }
    else if(WStechnique == 3){
        freq_shift = 50; // in Hz
        offset_asymWS = freq_shift * 50000 * (360. / (2*1000000));
    }
    else if(WStechnique == 7){
        freq_shift = 0L; // in Hz, initially was placed 12.5 CF
        // offset_HGWS = freq_shift * 30000 * (360. / (2*1000000));
        offset_HGWS = 0L;
    }
    else{
        freq_shift = 0L;
        offset_asymWS = 0L;
    }
    

    std::cout<<"freq_shift: "<<freq_shift<<std::endl;
    std::cout<<"offset_asymWS: "<<offset_asymWS<<std::endl;

    // Asym factor CF 

    if (WStechnique == 3){
        asym_factor = 334./400.;
    }
    else if(WStechnique == 4 || WStechnique == 5 || WStechnique == 9 || WStechnique == 10){
        asym_factor = 315./400.;
    }
    else if(WStechnique == 6){
        asym_factor = 296./400.;
    }
    else if(WStechnique == 7){
        asym_factor = 350./400;
    }

    std::cout<<"asym factor:"<< asym_factor<< std::endl;

    m_lis_watsup = 1;  // prep of RF and WET-spoiling is done   
    if(  mainNucleus != NUCLEUS_1H || rMrProt.preparationPulses().getlFatWaterContrast() == FatWaterContrast_Standard) 
       // wat.suppr. does not go together with X-nuclei receive  and in case Water Supp = None : no prep should be done
       m_lis_watsup = 0; 

    m_lis_watsupRF = 0;
    if ( rMrProt.preparationPulses().getlFatWaterContrast() == FatWaterContrast_WaterSaturation||
       rMrProt.preparationPulses().getlFatWaterContrast() == FatWaterContrast_WaterSuppressionWeak)
      m_lis_watsupRF = 1;
    
    // call chess in the main sequence

    if (WStechnique == 8)
    {
        SEQ_TRACE_WARN.print("Warning: prepping CHESS pulses = %d", WStechnique);

        m_rf_ws1.setTypeExcitation();
        m_rf_ws1.setDuration( 25600 ) ; // in us
        m_rf_ws1.setSamples( 25600/100 );
        m_rf_ws1.setFlipAngle( 89.2 );
        m_rf_ws1.setInitialPhase( 0.0 ); // not used
        m_rf_ws1.setThickness( 10.0 ); // not used
        m_rf_ws1.setFlipAngleCorrection();
        if( ! ( m_rf_ws1.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print("\nfSEQPrep():  %s\n",
                        "can't prepare water suppression pulse" );
                return m_rf_ws1.getNLSStatus();
        }

		// std::cout<<"m_bvap: "<<m_bvap<<std::endl;
        m_rf_ws2.setTypeExcitation();
        m_rf_ws2.setDuration( 25600 ) ; // in us
        m_rf_ws2.setSamples( 25600/100 );
        m_rf_ws2.setFlipAngle( 83.4 );
        m_rf_ws2.setInitialPhase( 0.0 ); // not used
        m_rf_ws2.setThickness( 10.0 ); // not used
        m_rf_ws2.setFlipAngleCorrection();
        if( ! ( m_rf_ws2.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print( "\nfSEQPrep():  %s\n",
                        "can't prepare water suppression pulse" );
                return m_rf_ws2.getNLSStatus();
        }

        m_rf_ws3.setTypeExcitation();
        m_rf_ws3.setDuration( 25600 ) ; // in us
        m_rf_ws3.setSamples( 25600/100 );
        m_rf_ws3.setFlipAngle( 160.8 );
        m_rf_ws3.setInitialPhase( 0.0 ); // not used
        m_rf_ws3.setThickness( 10.0 ); // not used
        m_rf_ws3.setFlipAngleCorrection();
        if( ! ( m_rf_ws3.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print( "\nfSEQPrep():  %s\n",
                        "can't prepare water suppression pulse" );
                return m_rf_ws3.getNLSStatus();
        }

		m_ph_s_ws.setFrequency( 0L );
        m_ph_n_ws.setFrequency( 0L );
        m_ph_s_ws.setPhase( 0 );
        m_ph_n_ws.setPhase( 0 );

		SEQ_TRACE_WARN.print("Warning: FINISHED prepping CHESS pulses = %d", WStechnique);

	}

    // // calculate pulses

    if (WStechnique == 1)
    {
        SEQ_TRACE_WARN.print("Warning: prepping VAPOR pulses = %f", WStechnique);

        m_rf_vapor1.setTypeExcitation();
        m_rf_vapor1.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor1.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor1.setFlipAngle( beta_multiplier_1*beta_vapor );
        m_rf_vapor1.setInitialPhase( 0.0 ); // not used
        m_rf_vapor1.setThickness( 10.0 ); // not used
        // m_rf_vapor1.setFlipAngleCorrection();
        if( ! ( m_rf_vapor1.prepGauss( rMrProt, rSeqExpo, VAPOR_bw )))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                return m_rf_vapor1.getNLSStatus();
        }


        m_rf_vapor2.setTypeExcitation();
        m_rf_vapor2.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor2.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor2.setFlipAngle( beta_multiplier_2*beta_vapor );
        m_rf_vapor2.setInitialPhase( 0.0 ); // not used
        m_rf_vapor2.setThickness( 10.0 ); // not used
        // m_rf_vapor2.setFlipAngleCorrection();
        if( ! ( m_rf_vapor2.prepGauss( rMrProt, rSeqExpo, VAPOR_bw )))
        {       
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor2.getNLSStatus();
        }

        m_rf_vapor3.setTypeExcitation();
        m_rf_vapor3.setDuration( VAPOR_RF_dur ) ; // in us MIGHT BE A PROBLEM 10NS MINIMUM
        m_rf_vapor3.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor3.setFlipAngle( beta_multiplier_3*beta_vapor ); 
        m_rf_vapor3.setInitialPhase( 0.0 ); // not used
        m_rf_vapor3.setThickness( 10.0 ); // not used
        // m_rf_vapor3.setFlipAngleCorrection();
        if (!(m_rf_vapor3.prepGauss(rMrProt, rSeqExpo, VAPOR_bw)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor3.getNLSStatus();
        }

        m_rf_vapor4.setTypeExcitation();
        m_rf_vapor4.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor4.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor4.setFlipAngle( beta_multiplier_4*beta_vapor );
        m_rf_vapor4.setInitialPhase( 0.0 ); // not used
        m_rf_vapor4.setThickness( 10.0 ); // not used
        // m_rf_vapor4.setFlipAngleCorrection();
        if (!(m_rf_vapor4.prepGauss(rMrProt, rSeqExpo, VAPOR_bw)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor4.getNLSStatus();
        }

        m_rf_vapor5.setTypeExcitation();
        m_rf_vapor5.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor5.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor5.setFlipAngle( beta_multiplier_5*beta_vapor );
        m_rf_vapor5.setInitialPhase( 0.0 ); // not used
        m_rf_vapor5.setThickness( 10.0 ); // not used
        // m_rf_vapor5.setFlipAngleCorrection();
        if (!(m_rf_vapor5.prepGauss(rMrProt, rSeqExpo, VAPOR_bw)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor5.getNLSStatus();
        }

        m_rf_vapor6.setTypeExcitation();
        m_rf_vapor6.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor6.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor6.setFlipAngle( beta_multiplier_6*beta_vapor );
        m_rf_vapor6.setInitialPhase( 0.0 ); // not used
        m_rf_vapor6.setThickness( 10.0 ); // not used
        // m_rf_vapor6.setFlipAngleCorrection();
        if (!(m_rf_vapor6.prepGauss(rMrProt, rSeqExpo, VAPOR_bw)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor6.getNLSStatus();
        }

        m_rf_vapor7.setTypeExcitation();
        m_rf_vapor7.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor7.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor7.setFlipAngle( beta_multiplier_7*beta_vapor );
        m_rf_vapor7.setInitialPhase( 0.0 ); // not used
        m_rf_vapor7.setThickness( 10.0 ); // not used
        // m_rf_vapor7.setFlipAngleCorrection();
        if (!(m_rf_vapor7.prepGauss(rMrProt, rSeqExpo, VAPOR_bw)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor7.getNLSStatus();
        }

        m_rf_vapor8.setTypeExcitation();
        m_rf_vapor8.setDuration( VAPOR_RF_dur ) ; // in us
        m_rf_vapor8.setSamples( VAPOR_RF_dur/100 );
        m_rf_vapor8.setFlipAngle( beta_multiplier_8*beta_vapor ); 
        m_rf_vapor8.setInitialPhase( 0.0 ); // not used
        m_rf_vapor8.setThickness( 10.0 ); // not used
        // m_rf_vapor8.setFlipAngleCorrection();
        if (!(m_rf_vapor8.prepGauss(rMrProt, rSeqExpo, VAPOR_bw)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_vapor8.getNLSStatus();
        }
    
        m_ph_s_vapor1.setFrequency( 0L ); // CF
        m_ph_n_vapor1.setFrequency( 0L );
        m_ph_s_vapor1.setPhase( 0 );
        m_ph_n_vapor1.setPhase( 0 );

        m_ph_s_vapor2.setFrequency( 0L );
        m_ph_n_vapor2.setFrequency( 0L );
        m_ph_s_vapor2.setPhase( 0 );
        m_ph_n_vapor2.setPhase( 0 );

        m_ph_s_vapor3.setFrequency( 0L );
        m_ph_n_vapor3.setFrequency( 0L );
        m_ph_s_vapor3.setPhase( 0 );
        m_ph_n_vapor3.setPhase( 0 );
        
        m_ph_s_vapor4.setFrequency( 0L );
        m_ph_n_vapor4.setFrequency( 0L );
        m_ph_s_vapor4.setPhase( 0 );
        m_ph_n_vapor4.setPhase( 0 );

        m_ph_s_vapor5.setFrequency( 0L );
        m_ph_n_vapor5.setFrequency( 0L );
        m_ph_s_vapor5.setPhase( 0 );
        m_ph_n_vapor5.setPhase( 0 );


        m_ph_s_vapor6.setFrequency( 0L );
        m_ph_n_vapor6.setFrequency( 0L );
        m_ph_s_vapor6.setPhase( 0 );
        m_ph_n_vapor6.setPhase( 0 );

        m_ph_s_vapor7.setFrequency( 0L );
        m_ph_n_vapor7.setFrequency( 0L );
        m_ph_s_vapor7.setPhase( 0 );
        m_ph_n_vapor7.setPhase( 0 );

        m_ph_s_vapor8.setFrequency( 0L );
        m_ph_n_vapor8.setFrequency( 0L );
        m_ph_s_vapor8.setPhase( 0 );
        m_ph_n_vapor8.setPhase( 0 );

        SEQ_TRACE_WARN.print("Warning: FINISHED prepping VAPOR pulses = %f", WStechnique);
    }

    else if(WStechnique == 2){
        SEQ_TRACE_WARN.print("Warning: prepping FAST pulses = %ld", WStechnique);
        m_rf_fast1.setTypeExcitation();
        m_rf_fast1.setDuration( FASTpulsedur_1_4 ) ; // in us
        m_rf_fast1.setSamples( FASTpulsedur_1_4/100 );
        m_rf_fast1.setFlipAngle( 100 ); 
        m_rf_fast1.setInitialPhase( 0.0 ); // not used
        m_rf_fast1.setThickness( 10.0 ); // not used
        // m_rf_fast1.setFlipAngleCorrection();
        if( ! ( m_rf_fast1.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_fast1.getNLSStatus();
        }

        m_rf_fast2.setTypeExcitation();
        m_rf_fast2.setDuration( FASTpulsedur_1_4 ) ; // in us
        m_rf_fast2.setSamples( FASTpulsedur_1_4/100 );
        m_rf_fast2.setFlipAngle( 80 ); 
        m_rf_fast2.setInitialPhase( 0.0 ); // not used
        m_rf_fast2.setThickness( 10.0 ); // not used
        // m_rf_fast2.setFlipAngleCorrection();
        if( ! ( m_rf_fast2.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_fast2.getNLSStatus();
        }		

        m_rf_fast3.setTypeExcitation();
        m_rf_fast3.setDuration( FASTpulsedur_1_4 ) ; // in us
        m_rf_fast3.setSamples( FASTpulsedur_1_4/100 );
        m_rf_fast3.setFlipAngle( 125 ); 
        m_rf_fast3.setInitialPhase( 0.0 ); // not used
        m_rf_fast3.setThickness( 10.0 ); // not used
        // m_rf_fast3.setFlipAngleCorrection();
        if( ! ( m_rf_fast3.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_fast3.getNLSStatus();
        }		

        m_rf_fast4.setTypeExcitation();
        m_rf_fast4.setDuration( FASTpulsedur_1_4 ) ; // in us
        m_rf_fast4.setSamples( FASTpulsedur_1_4/100 );
        m_rf_fast4.setFlipAngle( 65 ); 
        m_rf_fast4.setInitialPhase( 0.0 ); // not used
        m_rf_fast4.setThickness( 10.0 ); // not used
        // m_rf_fast4.setFlipAngleCorrection();
        if( ! ( m_rf_fast4.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_fast4.getNLSStatus();
        }		

        m_rf_fast5.setTypeExcitation();
        m_rf_fast5.setDuration( FASTpulsedur_5 ) ; // in us
        m_rf_fast5.setSamples( FASTpulsedur_5/100 );
        m_rf_fast5.setFlipAngle( 170 ); 
        m_rf_fast5.setInitialPhase( 0.0 ); // not used
        m_rf_fast5.setThickness( 10.0 ); // not used
        // m_rf_fast5.setFlipAngleCorrection();
        if( ! ( m_rf_fast5.prepGauss( rMrProt, rSeqExpo, 35. )))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_rf_fast5.getNLSStatus();
        }		

        m_ph_s_fast1.setFrequency( 0L );
        m_ph_n_fast1.setFrequency( 0L );
        m_ph_s_fast1.setPhase( 0 );
        m_ph_n_fast1.setPhase( 0 );

        m_ph_s_fast2.setFrequency( 0L );
        m_ph_n_fast2.setFrequency( 0L );
        m_ph_s_fast2.setPhase( 0 );
        m_ph_n_fast2.setPhase( 0 );

        m_ph_s_fast3.setFrequency( 0L );
        m_ph_n_fast3.setFrequency( 0L );
        m_ph_s_fast3.setPhase( 0 );
        m_ph_n_fast3.setPhase( 0 );

        m_ph_s_fast4.setFrequency( 0L );
        m_ph_n_fast4.setFrequency( 0L );
        m_ph_s_fast4.setPhase( 0 );
        m_ph_n_fast4.setPhase( 0 );

        m_ph_s_fast5.setFrequency( 0L );
        m_ph_n_fast5.setFrequency( 0L );
        m_ph_s_fast5.setPhase( 0 );
        m_ph_n_fast5.setPhase( 0 );

        SEQ_TRACE_WARN.print("Warning: FINISHED prepping FAST pulses = %f", WStechnique);

    }

    else if(WStechnique == 7){ // HGWS
        SEQ_TRACE_WARN.print("Warning: prepping HGWS pulses = %f", WStechnique);
        m_HG1.setTypeUndefined();
        m_HG1.setDuration( 30000 ) ;
        m_HG1.setFlipAngle( 74.2 );
        m_HG1.setInitialPhase( 0.0 );
        m_HG1.setFamilyName( m_HG );
        m_HG1.setThickness(  10.0 );
        SEQ_TRACE_WARN.print("m_HG 1");
        if( ! ( m_HG1.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_HG1.getNLSStatus();
        }

        m_HG2.setTypeUndefined();
        m_HG2.setDuration( 30000 ) ;
        m_HG2.setFlipAngle( 91.9 );
        m_HG2.setInitialPhase( 0.0 );
        m_HG2.setFamilyName( m_HG );
        m_HG2.setThickness(  10.0 );
        if( ! ( m_HG2.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_HG2.getNLSStatus();
        }

        m_HG3.setTypeUndefined();
        m_HG3.setDuration( 30000 ) ;
        m_HG3.setFlipAngle( 68.4 );
        m_HG3.setInitialPhase( 0.0 );
        m_HG3.setFamilyName( m_HG );
        m_HG3.setThickness(  10.0 );
        if( ! ( m_HG3.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_HG3.getNLSStatus();
        }

        m_HG4.setTypeUndefined();
        m_HG4.setDuration( 30000 ) ;
        m_HG4.setFlipAngle( 83.3 );
        m_HG4.setInitialPhase( 0.0 );
        m_HG4.setFamilyName( m_HG );
        m_HG4.setThickness(  10.0 );
        if( ! ( m_HG4.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_HG4.getNLSStatus();
        }

        m_HG5.setTypeUndefined();
        m_HG5.setDuration( 30000 ) ;
        m_HG5.setFlipAngle( 142.5 );
        m_HG5.setInitialPhase( 0.0 );
        m_HG5.setFamilyName( m_HG );
        m_HG5.setThickness(  10.0 );
        if( ! ( m_HG5.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_HG5.getNLSStatus();
        }

        m_ph_s_HG1.setFrequency( freq_shift );
        m_ph_n_HG1.setFrequency( 0L );
        m_ph_s_HG1.setPhase( -offset_HGWS );
        m_ph_n_HG1.setPhase( -offset_HGWS );

        m_ph_s_HG2.setFrequency( freq_shift );
        m_ph_n_HG2.setFrequency( 0L );
        m_ph_s_HG2.setPhase( -offset_HGWS );
        m_ph_n_HG2.setPhase( -offset_HGWS );

        m_ph_s_HG3.setFrequency( freq_shift );
        m_ph_n_HG3.setFrequency( 0L );
        m_ph_s_HG3.setPhase( -offset_HGWS );
        m_ph_n_HG3.setPhase( -offset_HGWS );

        m_ph_s_HG4.setFrequency( freq_shift );
        m_ph_n_HG4.setFrequency( 0L );
        m_ph_s_HG4.setPhase( -offset_HGWS );
        m_ph_n_HG4.setPhase( -offset_HGWS );

        m_ph_s_HG5.setFrequency( freq_shift );
        m_ph_n_HG5.setFrequency( 0L );
        m_ph_s_HG5.setPhase( -offset_HGWS );
        m_ph_n_HG5.setPhase( -offset_HGWS );
        
        SEQ_TRACE_WARN.print("Warning: FINISHED prepping HGWS pulses = %f", WStechnique);

    }
    
    else if(WStechnique == 3 || WStechnique == 4 || WStechnique == 6 ){

        SEQ_TRACE_WARN.print("Warning: prepping asym pulses = %f", WStechnique);

        m_vap_asym1.setTypeUndefined();
        m_vap_asym1.setDuration(VAPOR_RF_dur);
        m_vap_asym1.setFlipAngle( beta_multiplier_1*beta_vapor );
        m_vap_asym1.setInitialPhase( 0.0 );
        m_vap_asym1.setFamilyName( m_asym_sinc );
        m_vap_asym1.setThickness(  10.0 );
        if( ! ( m_vap_asym1.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym1.getNLSStatus();
        }

        m_vap_asym2.setTypeUndefined();
        m_vap_asym2.setDuration(VAPOR_RF_dur);
        m_vap_asym2.setFlipAngle( beta_multiplier_2*beta_vapor );
        m_vap_asym2.setInitialPhase( 0.0 );
        m_vap_asym2.setFamilyName( m_asym_sinc );
        m_vap_asym2.setThickness(  10.0 );
        if( ! ( m_vap_asym2.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym2.getNLSStatus();
        }

        m_vap_asym3.setTypeUndefined();
        m_vap_asym3.setDuration(VAPOR_RF_dur);
        m_vap_asym3.setFlipAngle( beta_multiplier_3*beta_vapor );
        m_vap_asym3.setInitialPhase( 0.0 );
        m_vap_asym3.setFamilyName( m_asym_sinc );
        m_vap_asym3.setThickness(  10.0 );
        if( ! ( m_vap_asym3.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym3.getNLSStatus();
        }

        m_vap_asym4.setTypeUndefined();
        m_vap_asym4.setDuration(VAPOR_RF_dur);
        m_vap_asym4.setFlipAngle( beta_multiplier_4*beta_vapor );
        m_vap_asym4.setInitialPhase( 0.0 );
        m_vap_asym4.setFamilyName( m_asym_sinc );
        m_vap_asym4.setThickness(  10.0 );
        if( ! ( m_vap_asym4.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym4.getNLSStatus();
        }

        m_vap_asym5.setTypeUndefined();
        m_vap_asym5.setDuration(VAPOR_RF_dur);
        m_vap_asym5.setFlipAngle( beta_multiplier_5*beta_vapor );
        m_vap_asym5.setInitialPhase( 0.0 );
        m_vap_asym5.setFamilyName( m_asym_sinc );
        m_vap_asym5.setThickness(  10.0 );
        if( ! ( m_vap_asym5.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym5.getNLSStatus();
        }

        m_vap_asym6.setTypeUndefined();
        m_vap_asym6.setDuration(VAPOR_RF_dur);
        m_vap_asym6.setFlipAngle( beta_multiplier_6*beta_vapor );
        m_vap_asym6.setInitialPhase( 0.0 );
        m_vap_asym6.setFamilyName( m_asym_sinc );
        m_vap_asym6.setThickness(  10.0 );
        if( ! ( m_vap_asym6.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym6.getNLSStatus();
        }

        m_vap_asym7.setTypeUndefined();
        m_vap_asym7.setDuration(VAPOR_RF_dur);
        m_vap_asym7.setFlipAngle( beta_multiplier_7*beta_vapor );
        m_vap_asym7.setInitialPhase( 0.0 );
        m_vap_asym7.setFamilyName( m_asym_sinc );
        m_vap_asym7.setThickness(  10.0 );
        if( ! ( m_vap_asym7.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym7.getNLSStatus();
        }

        m_vap_asym8.setTypeUndefined();
        m_vap_asym8.setDuration(VAPOR_RF_dur);
        m_vap_asym8.setFlipAngle( beta_multiplier_8*beta_vapor );
        m_vap_asym8.setInitialPhase( 0.0 );
        m_vap_asym8.setFamilyName( m_asym_sinc );
        m_vap_asym8.setThickness(  10.0 );
        if( ! ( m_vap_asym8.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym8.getNLSStatus();
        }

        m_ph_s_asym1.setFrequency( freq_shift );
        m_ph_n_asym1.setFrequency( 0L );
        m_ph_s_asym1.setPhase( -offset_asymWS );
        m_ph_n_asym1.setPhase( -offset_asymWS );

        m_ph_s_asym2.setFrequency( freq_shift );
        m_ph_n_asym2.setFrequency( 0L );
        m_ph_s_asym2.setPhase( -offset_asymWS );
        m_ph_n_asym2.setPhase( -offset_asymWS );

        m_ph_s_asym3.setFrequency( freq_shift );
        m_ph_n_asym3.setFrequency( 0L );
        m_ph_s_asym3.setPhase( -offset_asymWS );
        m_ph_n_asym3.setPhase( -offset_asymWS );

        m_ph_s_asym4.setFrequency( freq_shift );
        m_ph_n_asym4.setFrequency( 0L );
        m_ph_s_asym4.setPhase( -offset_asymWS );
        m_ph_n_asym4.setPhase( -offset_asymWS );

        m_ph_s_asym5.setFrequency( freq_shift );
        m_ph_n_asym5.setFrequency( 0L );
        m_ph_s_asym5.setPhase( -offset_asymWS );
        m_ph_n_asym5.setPhase( -offset_asymWS );

        m_ph_s_asym6.setFrequency( freq_shift );
        m_ph_n_asym6.setFrequency( 0L );
        m_ph_s_asym6.setPhase( -offset_asymWS );
        m_ph_n_asym6.setPhase( -offset_asymWS ); //

        m_ph_s_asym7.setFrequency( freq_shift );
        m_ph_n_asym7.setFrequency( 0L );
        m_ph_s_asym7.setPhase( -offset_asymWS );
        m_ph_n_asym7.setPhase( -offset_asymWS ); //

        m_ph_s_asym8.setFrequency( freq_shift );
        m_ph_n_asym8.setFrequency( 0L );
        m_ph_s_asym8.setPhase( -offset_asymWS );
        m_ph_n_asym8.setPhase( -offset_asymWS );

        SEQ_TRACE_WARN.print("Warning: FINISHED prepping asym pulses = %f", WStechnique);

    }

    else if(WStechnique == 9){ // 5 pulses
        SEQ_TRACE_WARN.print("Warning: prepping asym pulses = %f", WStechnique);

        m_vap_asym1.setTypeUndefined();
        m_vap_asym1.setDuration(VAPOR_RF_dur);
        m_vap_asym1.setFlipAngle( beta_multiplier_1*beta_vapor );
        m_vap_asym1.setInitialPhase( 0.0 );
        m_vap_asym1.setFamilyName( m_asym_sinc );
        m_vap_asym1.setThickness(  10.0 );
        if( ! ( m_vap_asym1.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym1.getNLSStatus();
        }

        m_vap_asym2.setTypeUndefined();
        m_vap_asym2.setDuration(VAPOR_RF_dur);
        m_vap_asym2.setFlipAngle( beta_multiplier_2*beta_vapor );
        m_vap_asym2.setInitialPhase( 0.0 );
        m_vap_asym2.setFamilyName( m_asym_sinc );
        m_vap_asym2.setThickness(  10.0 );
        if( ! ( m_vap_asym2.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym2.getNLSStatus();
        }

        m_vap_asym3.setTypeUndefined();
        m_vap_asym3.setDuration(VAPOR_RF_dur);
        m_vap_asym3.setFlipAngle( beta_multiplier_3*beta_vapor );
        m_vap_asym3.setInitialPhase( 0.0 );
        m_vap_asym3.setFamilyName( m_asym_sinc );
        m_vap_asym3.setThickness(  10.0 );
        if( ! ( m_vap_asym3.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym3.getNLSStatus();
        }

        m_vap_asym4.setTypeUndefined();
        m_vap_asym4.setDuration(VAPOR_RF_dur);
        m_vap_asym4.setFlipAngle( beta_multiplier_4*beta_vapor );
        m_vap_asym4.setInitialPhase( 0.0 );
        m_vap_asym4.setFamilyName( m_asym_sinc );
        m_vap_asym4.setThickness(  10.0 );
        if( ! ( m_vap_asym4.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym4.getNLSStatus();
        }

        m_vap_asym5.setTypeUndefined();
        m_vap_asym5.setDuration(VAPOR_RF_dur);
        m_vap_asym5.setFlipAngle( beta_multiplier_5*beta_vapor );
        m_vap_asym5.setInitialPhase( 0.0 );
        m_vap_asym5.setFamilyName( m_asym_sinc );
        m_vap_asym5.setThickness(  10.0 );
        if( ! ( m_vap_asym5.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym5.getNLSStatus();
        }

        m_ph_s_asym1.setFrequency( freq_shift );
        m_ph_n_asym1.setFrequency( 0L );
        m_ph_s_asym1.setPhase( -offset_asymWS );
        m_ph_n_asym1.setPhase( -offset_asymWS );

        m_ph_s_asym2.setFrequency( freq_shift );
        m_ph_n_asym2.setFrequency( 0L );
        m_ph_s_asym2.setPhase( -offset_asymWS );
        m_ph_n_asym2.setPhase( -offset_asymWS );

        m_ph_s_asym3.setFrequency( freq_shift );
        m_ph_n_asym3.setFrequency( 0L );
        m_ph_s_asym3.setPhase( -offset_asymWS );
        m_ph_n_asym3.setPhase( -offset_asymWS );

        m_ph_s_asym4.setFrequency( freq_shift );
        m_ph_n_asym4.setFrequency( 0L );
        m_ph_s_asym4.setPhase( -offset_asymWS );
        m_ph_n_asym4.setPhase( -offset_asymWS );

        m_ph_s_asym5.setFrequency( freq_shift );
        m_ph_n_asym5.setFrequency( 0L );
        m_ph_s_asym5.setPhase( -offset_asymWS );
        m_ph_n_asym5.setPhase( -offset_asymWS );

        SEQ_TRACE_WARN.print("Warning: FINISHED prepping asym pulses = %f", WStechnique);
    }

    else if( WStechnique == 5){ // jn_asym_50 4 pulses with 50ms
        SEQ_TRACE_WARN.print("Warning: prepping asym pulses = %f", WStechnique);

        m_vap_asym1.setTypeUndefined();
        m_vap_asym1.setDuration( 50000 ) ;
        m_vap_asym1.setFlipAngle( beta_multiplier_1*beta_vapor );
        m_vap_asym1.setInitialPhase( 0.0 );
        m_vap_asym1.setFamilyName( m_asym_sinc );
        m_vap_asym1.setThickness(  10.0 );
        if( ! ( m_vap_asym1.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym1.getNLSStatus();
        }

        m_vap_asym2.setTypeUndefined();
        m_vap_asym2.setDuration(50000);
        m_vap_asym2.setFlipAngle( beta_multiplier_2*beta_vapor );
        m_vap_asym2.setInitialPhase( 0.0 );
        m_vap_asym2.setFamilyName( m_asym_sinc );
        m_vap_asym2.setThickness(  10.0 );
        if( ! ( m_vap_asym2.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym2.getNLSStatus();
        }

        m_vap_asym3.setTypeUndefined();
        m_vap_asym3.setDuration(50000);
        m_vap_asym3.setFlipAngle( beta_multiplier_3*beta_vapor );
        m_vap_asym3.setInitialPhase( 0.0 );
        m_vap_asym3.setFamilyName( m_asym_sinc );
        m_vap_asym3.setThickness(  10.0 );
        if( ! ( m_vap_asym3.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym3.getNLSStatus();
        }

        m_vap_asym4.setTypeUndefined();
        m_vap_asym4.setDuration(50000);
        m_vap_asym4.setFlipAngle( beta_multiplier_4*beta_vapor );
        m_vap_asym4.setInitialPhase( 0.0 );
        m_vap_asym4.setFamilyName( m_asym_sinc );
        m_vap_asym4.setThickness(  10.0 );
        if( ! ( m_vap_asym4.prepExternal( rMrProt, rSeqExpo)))
        {
                SEQ_TRACE_WARN.print("can't prepare water suppression pulse");
                // TRACE_PUT1(TC_INFO, TF_SEQ, "\nfSEQPrep():  %s\n",
                //         "can't prepare water suppression pulse" );
                return m_vap_asym4.getNLSStatus();
        }

        m_ph_s_asym1.setFrequency( freq_shift );
        m_ph_n_asym1.setFrequency( 0L );
        m_ph_s_asym1.setPhase( -offset_asymWS );
        m_ph_n_asym1.setPhase( -offset_asymWS );

        m_ph_s_asym2.setFrequency( freq_shift );
        m_ph_n_asym2.setFrequency( 0L );
        m_ph_s_asym2.setPhase( -offset_asymWS );
        m_ph_n_asym2.setPhase( -offset_asymWS );

        m_ph_s_asym3.setFrequency( freq_shift );
        m_ph_n_asym3.setFrequency( 0L );
        m_ph_s_asym3.setPhase( -offset_asymWS );
        m_ph_n_asym3.setPhase( -offset_asymWS );

        m_ph_s_asym4.setFrequency( freq_shift );
        m_ph_n_asym4.setFrequency( 0L );
        m_ph_s_asym4.setPhase( -offset_asymWS );
        m_ph_n_asym4.setPhase( -offset_asymWS );

        SEQ_TRACE_WARN.print("Warning: FINISHED prepping asym pulses = %f", WStechnique);
    }

    if( m_lis_watsupRF )
    {
        if( WStechnique == 1 ){
            m_RFInfoPerRequest += m_rf_vapor1.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor2.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor3.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor4.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor5.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor6.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor7.getRFInfo();
            m_RFInfoPerRequest += m_rf_vapor8.getRFInfo();
            std::cout<<"UGHHH VAPOR PUHLEASEEE2"<<std::endl;
        }
        else if(WStechnique == 2){ // CF fast
            m_RFInfoPerRequest += m_rf_fast1.getRFInfo();
            m_RFInfoPerRequest += m_rf_fast2.getRFInfo();
            m_RFInfoPerRequest += m_rf_fast3.getRFInfo();
            m_RFInfoPerRequest += m_rf_fast4.getRFInfo();
            m_RFInfoPerRequest += m_rf_fast5.getRFInfo();
        }

        // call this in the main sequence

        else if(WStechnique == 8){
            m_RFInfoPerRequest += m_rf_ws1.getRFInfo();
            m_RFInfoPerRequest += m_rf_ws2.getRFInfo();
            m_RFInfoPerRequest += m_rf_ws3.getRFInfo();
        } 
        else if(WStechnique == 7){ // CF HGWS
            m_RFInfoPerRequest += m_HG1.getRFInfo();
            m_RFInfoPerRequest += m_HG2.getRFInfo();
            m_RFInfoPerRequest += m_HG3.getRFInfo();
            m_RFInfoPerRequest += m_HG4.getRFInfo();
            m_RFInfoPerRequest += m_HG5.getRFInfo();
            SEQ_TRACE_WARN.print("rfInfo from SBB watsup in SBB %ld", m_RFInfoPerRequest.getPulseEnergyWs());
        }
        else if(WStechnique == 3 || WStechnique == 4 || WStechnique == 6){
            m_RFInfoPerRequest += m_vap_asym1.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym2.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym3.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym4.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym5.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym6.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym7.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym8.getRFInfo();
            
        }
        else if(WStechnique == 9){
            m_RFInfoPerRequest += m_vap_asym1.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym2.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym3.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym4.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym5.getRFInfo();
        }
        else if(WStechnique == 5){
            m_RFInfoPerRequest += m_vap_asym1.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym2.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym3.getRFInfo();
            m_RFInfoPerRequest += m_vap_asym4.getRFInfo();
        }
    }

    SEQ_TRACE_WARN.print("HG_5");

    if (WStechnique == 1 || WStechnique == 3 || WStechnique == 4 || WStechnique == 6)
    {
        // Vapor spoilers CF
        SEQ_TRACE_WARN.print("prepping gradients");
        std::cout << "UGHHH VAPOR PUHLEASEEE" << std::endl;

        // if( !( m_vaporsp_1.prepAmplitude( m_vapSpRamp, m_vaporsp_dur, m_vapSpRamp, m_vaporsp_1amp ) ) || !(
        // m_vaporsp_1.check() ) )
        // {
        //     std::cout << "m_vaporsp_1.prepAmplitude failed" <<std::endl;
        //     return m_vaporsp_1.getNLSStatus();
        // }

        if (!SpecUtils::prepGradient(m_vaporsp_1, m_vaporsp_1amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_1.check()))
        {
            std::cout << "m_vaporsp_1.prepAmplitude failed" << std::endl;
            return m_vaporsp_1.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_2, m_vaporsp_2amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_2.check()))
        {
            std::cout << "m_vaporsp_2.prepAmplitude failed" << std::endl;
            return m_vaporsp_2.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_3, m_vaporsp_3amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_3.check()))
        {
            std::cout << "m_vaporsp_3.prepAmplitude failed" << std::endl;
            return m_vaporsp_3.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_4, m_vaporsp_4amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_4.check()))
        {
            std::cout << "m_vaporsp_4.prepAmplitude failed" << std::endl;
            return m_vaporsp_4.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_5, m_vaporsp_5amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_5.check()))
        {
            std::cout << "m_vaporsp_5.prepAmplitude failed" << std::endl;
            return m_vaporsp_5.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_6, m_vaporsp_6amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_6.check()))
        {
            std::cout << "m_vaporsp_6.prepAmplitude failed" << std::endl;
            return m_vaporsp_6.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_7, m_vaporsp_7amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_7.check()))
        {
            std::cout << "m_vaporsp_7.prepAmplitude failed" << std::endl;
            return m_vaporsp_7.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_8, m_vaporsp_8amp_1, m_vaporsp_dur, m_vapSpRamp)
            || !(m_vaporsp_8.check()))
        {
            std::cout << "m_vaporsp_8.prepAmplitude failed" << std::endl;
            return m_vaporsp_8.getNLSStatus();
        }
        std::cout << "HEHE4: " << std::endl;
        SEQ_TRACE_WARN.print("finished prepping gradients");
    }

    if (WStechnique == 9)
    {
        if (!SpecUtils::prepGradient(m_vaporsp_1, m_vaporsp_1amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_1.check()))
        {
            std::cout << "m_vaporsp_1.prepAmplitude failed" << std::endl;
            return m_vaporsp_1.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_2, m_vaporsp_2amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_2.check()))
        {
            std::cout << "m_vaporsp_2.prepAmplitude failed" << std::endl;
            return m_vaporsp_2.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_3, m_vaporsp_3amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_3.check()))
        {
            std::cout << "m_vaporsp_3.prepAmplitude failed" << std::endl;
            return m_vaporsp_3.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_4, m_vaporsp_4amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_4.check()))
        {
            std::cout << "m_vaporsp_4.prepAmplitude failed" << std::endl;
            return m_vaporsp_4.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_5, m_vaporsp_5amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_5.check()))
        {
            std::cout << "m_vaporsp_5.prepAmplitude failed" << std::endl;
            return m_vaporsp_5.getNLSStatus();
        }
    }

    if (WStechnique == 5)
    {
        if (!SpecUtils::prepGradient(m_vaporsp_1, m_vaporsp_1amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_1.check()))
        {
            std::cout << "m_vaporsp_1.prepAmplitude failed" << std::endl;
            return m_vaporsp_1.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_2, m_vaporsp_2amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_2.check()))
        {
            std::cout << "m_vaporsp_2.prepAmplitude failed" << std::endl;
            return m_vaporsp_2.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_3, m_vaporsp_3amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_3.check()))
        {
            std::cout << "m_vaporsp_3.prepAmplitude failed" << std::endl;
            return m_vaporsp_3.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_vaporsp_4, m_vaporsp_4amp, m_vaporsp_dur, m_vapSpRamp) || !(m_vaporsp_4.check()))
        {
            std::cout << "m_vaporsp_4.prepAmplitude failed" << std::endl;
            return m_vaporsp_4.getNLSStatus();
        }
    }

    if (WStechnique == 7) // CF HGWS
    {
        SEQ_TRACE_WARN.print("HG_8");
        if (!SpecUtils::prepGradient(m_HGsp_1, m_HGsp_1_3amp, m_HGsp_dur, m_HGSpRamp) || !(m_HGsp_1.check()))
        {
            std::cout << "m_HGsp_1.prepAmplitude failed" << std::endl;
            return m_HGsp_1.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_HGsp_2, m_HGsp_1_3amp, m_HGsp_dur, m_HGSpRamp) || !(m_HGsp_2.check()))
        {
            std::cout << "m_HGsp_2.prepAmplitude failed" << std::endl;
            return m_HGsp_2.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_HGsp_3, m_HGsp_1_3amp, m_HGsp_dur, m_HGSpRamp) || !(m_HGsp_3.check()))
        {
            std::cout << "m_HGsp_3.prepAmplitude failed" << std::endl;
            return m_HGsp_3.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_HGsp_4, m_HGsp_4amp, m_HGsp_dur, m_HGSpRamp) || !(m_HGsp_4.check()))
        {
            std::cout << "m_HGsp_4.prepAmplitude failed" << std::endl;
            return m_HGsp_4.getNLSStatus();
        }

        if (!SpecUtils::prepGradient(m_HGsp_5, m_HGsp_5amp, m_HGsp_dur, m_HGSpRamp) || !(m_HGsp_5.check()))
        {
            std::cout << "m_HGsp_5.prepAmplitude failed" << std::endl;
            return m_HGsp_5.getNLSStatus();
        }
    }

    if (WStechnique == 2)
    {
        // FAST spoilers CF

        if (!SpecUtils::prepGradient(m_fastsp_1, m_fastsp_1_3amp, m_fastsp_dur_1_3, m_fastSpRamp)
            || !(m_fastsp_1.check()))
        {
            std::cout << "m_fastsp_1.prepAmplitude failed" << std::endl;
            return m_fastsp_1.getNLSStatus();
        }
        if (!SpecUtils::prepGradient(m_fastsp_2, m_fastsp_1_3amp, m_fastsp_dur_1_3, m_fastSpRamp)
            || !(m_fastsp_2.check()))
        {
            std::cout << "m_fastsp_2.prepAmplitude failed" << std::endl;
            return m_fastsp_2.getNLSStatus();
        }
        if (!SpecUtils::prepGradient(m_fastsp_3, m_fastsp_1_3amp, m_fastsp_dur_1_3, m_fastSpRamp)
            || !(m_fastsp_3.check()))
        {
            std::cout << "m_fastsp_3.prepAmplitude failed" << std::endl;
            return m_fastsp_3.getNLSStatus();
        }
        if (!SpecUtils::prepGradient(m_fastsp_4, m_fastsp_4amp, m_fastsp_dur_4, m_fastSpRamp) || !(m_fastsp_4.check()))
        {
            std::cout << "m_fastsp_4.prepAmplitude failed" << std::endl;
            return m_fastsp_4.getNLSStatus();
        }
        if (!SpecUtils::prepGradient(m_fastsp_5, m_fastsp_5amp, m_fastsp_dur_5, m_fastSpRamp) || !(m_fastsp_5.check()))
        {
            std::cout << "m_fastsp_5.prepAmplitude failed" << std::endl;
            return m_fastsp_5.getNLSStatus();
        }
    }

    if (WStechnique == 8)
    {
        if (!SpecUtils::prepGradient(m_wssp_ph, d, l, ramptime) || !(m_wssp_ph.check()))
            return m_wssp_ph.getNLSStatus();

        if (!SpecUtils::prepGradient(m_wssp_ro, d, l, ramptime) || !(m_wssp_ro.check()))
            return m_wssp_ro.getNLSStatus();

        if (!SpecUtils::prepGradient(m_wssp_sl, d, l, ramptime) || !(m_wssp_sl.check()))
            return m_wssp_sl.getNLSStatus();
    }

    if (WStechnique == 1) // CF VAPOR
    {
        SEQ_TRACE_WARN.print("prepping deadtimes");
		deadtime_1 = t1 - (.5 * ( m_rf_vapor1.getDuration() + m_rf_vapor2.getDuration() ) + m_vaporsp_1.getTotalTime() );
		std::cout<<"deadtime_1: "<< deadtime_1 <<std::endl;
        std::cout<<"calculating VAPOR asym deadtime"<<std::endl;
		if ( deadtime_1 < 0 )
		{ 
			std::cout<<"HEHE32: "<<std::endl;
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t1 = %ld us cannot be realized;\n"
                    "deadtime_1 %ld",
                    ptModule, t1, deadtime_1);
			}
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31: "<<std::endl;
		deadtime_2 = t2 - (.5 * ( m_rf_vapor2.getDuration() + m_rf_vapor3.getDuration() ) + m_vaporsp_2.getTotalTime() );
		if ( deadtime_2 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t2 = %ld us cannot be realized;\n"
                    "deadtime_2 %ld",
                    ptModule, t2, deadtime_2);
			}
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_3 = t3 - (.5 * ( m_rf_vapor3.getDuration() + m_rf_vapor4.getDuration() ) + m_vaporsp_3.getTotalTime() );
			if ( deadtime_3 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t3 = %ld us cannot be realized;\n"
                    "deadtime_3 %ld",
                    ptModule, t3, deadtime_3);
			}
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_4 = t4 - (.5 * ( m_rf_vapor4.getDuration() + m_rf_vapor5.getDuration() ) + m_vaporsp_4.getTotalTime() );
			if ( deadtime_4 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t4 = %ld us cannot be realized;\n"
                    "deadtime_4 %ld",
                    ptModule, t4, deadtime_4);
            }
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_5 = t5 - (.5 * ( m_rf_vapor5.getDuration() + m_rf_vapor6.getDuration() ) + m_vaporsp_5.getTotalTime() );
			 if ( deadtime_5 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t5 = %d us cannot be realized;\n"
                    "deadtime_5 %d",
                    ptModule, t5, deadtime_5);
			}
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_6 = t6 - (.5 * ( m_rf_vapor6.getDuration() + m_rf_vapor7.getDuration() ) + m_vaporsp_6.getTotalTime() );
			if ( deadtime_6 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) ){
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t6 = %d us cannot be realized;\n"
                    "deadtime_6 %d",
                    ptModule, t6, deadtime_6);
			}
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_7 = t7 - (.5 * ( m_rf_vapor7.getDuration() + m_rf_vapor8.getDuration() ) + m_vaporsp_7.getTotalTime() );
			if ( deadtime_7 < 0 )
		{ 
		    if( !(rSeqLim.isContextPrepForBinarySearch()) ){
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t7 = %d us cannot be realized;\n"
                    "deadtime_7 %d",
                    ptModule, t7, deadtime_7);
			}
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_8 = t8 - (.5 * ( m_rf_vapor8.getDuration() + m_rf_exc->getDuration() ) + m_vaporsp_8.getTotalTime() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()) );
			if ( deadtime_8 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) ){
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t8 = %d us cannot be realized;\n"
                    "deadtime_8 %d",
                    ptModule, t8, deadtime_8);  
			}
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
        SEQ_TRACE_WARN.print("finished prepping deadtimes");
	}

    if (WStechnique == 3 || WStechnique == 4 || WStechnique == 6) // VAPOR asym CF
    { 
		std::cout<<"calculating VAPOR asym deadtime"<<std::endl;
		deadtime_1 = t1 - ((1-asym_factor) *  m_vap_asym1.getDuration() + asym_factor*m_vap_asym2.getDuration() + m_vaporsp_1.getTotalTime() );
		std::cout<<"deadtime_1: "<< deadtime_1 <<std::endl;
		if ( deadtime_1 < 0 )
		{ 
			    std::cout<<"HEHE32: "<<std::endl;
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t1 = %d us cannot be realized;\n"
                        "deadtime_1 %d",
                        ptModule, t1, deadtime_1);
			    }  
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31: "<<std::endl;
		deadtime_2 = t2 - ((1-asym_factor) *  m_vap_asym2.getDuration() + asym_factor*m_vap_asym3.getDuration() + m_vaporsp_2.getTotalTime() );
		if ( deadtime_2 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t2 = %d us cannot be realized;\n"
                    "deadtime_2 %d",
                    ptModule, t2, deadtime_2);
			}
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31111: "<<std::endl;
		deadtime_3 = t3 - ((1-asym_factor)*m_vap_asym3.getDuration() + asym_factor*m_vap_asym4.getDuration() + m_vaporsp_3.getTotalTime() );
		if ( deadtime_3 < 0 )
		{ 
			  if( !(rSeqLim.isContextPrepForBinarySearch()) )
              {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t3 = %d us cannot be realized;\n"
                    "deadtime_3 %d",
                    ptModule, t3, deadtime_3);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31111: "<<std::endl;
		deadtime_4 = t4 - ((1-asym_factor)*m_vap_asym4.getDuration() + asym_factor*m_vap_asym5.getDuration() + m_vaporsp_4.getTotalTime() );
		if ( deadtime_4 < 0 )
		{ 
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t4 = %d us cannot be realized;\n"
                    "deadtime_4 %d",
                    ptModule, t4, deadtime_4); 
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_5 = t5 - ((1-asym_factor)*m_vap_asym5.getDuration() + asym_factor*m_vap_asym6.getDuration() + m_vaporsp_5.getTotalTime() );
		if ( deadtime_5 < 0 )
		{ 
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t5 = %d us cannot be realized;\n"
                        "deadtime_5 %d",
                        ptModule, t5, deadtime_5);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_6 = t6 - ((1-asym_factor)*m_vap_asym6.getDuration() + asym_factor*m_vap_asym7.getDuration() + m_vaporsp_6.getTotalTime() );
		if ( deadtime_6 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t6 = %d us cannot be realized;\n"
                        "deadtime_6 %d",
                        ptModule, t6, deadtime_6);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

		deadtime_7 = t7 - ((1-asym_factor)*m_vap_asym7.getDuration() + asym_factor*m_vap_asym8.getDuration() + m_vaporsp_7.getTotalTime() );
		if ( deadtime_7 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t7 = %d us cannot be realized;\n"
                    "deadtime_7 %d",
                    ptModule, t7, deadtime_7);
			}
			    return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
			 std::cout<<"HEHE3HOHO: "<<std::endl;

		deadtime_8 = t8 - ((1-asym_factor)*m_vap_asym8.getDuration() + 0.5*m_rf_exc->getDuration() + m_vaporsp_8.getTotalTime() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()) );
		std::cout<<"deadtime_8: "<< deadtime_8<< std::endl;
		if ( deadtime_8 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t8 = %d us cannot be realized;\n"
                    "deadtime_8 %d",
                    ptModule, t8, deadtime_8); 
			}
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
			std::cout<<"HEHE31112231: "<<std::endl;

	}

    if(WStechnique == 9){
        std::cout<<"calculating VAPOR asym deadtime"<<std::endl;
		deadtime_1 = t1 - ((1-asym_factor) *  m_vap_asym1.getDuration() + asym_factor*m_vap_asym2.getDuration() + m_vaporsp_1.getTotalTime() );
		std::cout<<"deadtime_1: "<< deadtime_1 <<std::endl;
		if ( deadtime_1 < 0 )
		{ 
			    std::cout<<"HEHE32: "<<std::endl;
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t1 = %d us cannot be realized;\n"
                        "deadtime_1 %d",
                        ptModule, t1, deadtime_1);
			    }  
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31: "<<std::endl;
		deadtime_2 = t2 - ((1-asym_factor) *  m_vap_asym2.getDuration() + asym_factor*m_vap_asym3.getDuration() + m_vaporsp_2.getTotalTime() );
        std::cout << "deadtime_2: " << deadtime_2 << std::endl;
		if ( deadtime_2 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t2 = %d us cannot be realized;\n"
                    "deadtime_2 %d",
                    ptModule, t2, deadtime_2);
			}
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31111: "<<std::endl;
		deadtime_3 = t3 - ((1-asym_factor)*m_vap_asym3.getDuration() + asym_factor*m_vap_asym4.getDuration() + m_vaporsp_3.getTotalTime() );
        std::cout << "deadtime_3: " << deadtime_3 << std::endl;
		if ( deadtime_3 < 0 )
		{ 
			  if( !(rSeqLim.isContextPrepForBinarySearch()) )
              {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t3 = %d us cannot be realized;\n"
                    "deadtime_3 %d",
                    ptModule, t3, deadtime_3);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31111: "<<std::endl;
		deadtime_4 = t4 - ((1-asym_factor)*m_vap_asym4.getDuration() + asym_factor*m_vap_asym5.getDuration() + m_vaporsp_4.getTotalTime() );
        std::cout << "deadtime_4: " << deadtime_4 << std::endl;
		if ( deadtime_4 < 0 )
		{ 
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t4 = %d us cannot be realized;\n"
                    "deadtime_4 %d",
                    ptModule, t4, deadtime_4); 
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
        
		// deadtime_5 = t5 - ((1-asym_factor)*m_vap_asym5.getDuration() + 0.5*m_rf_exc->getDuration() + m_vaporsp_5.getTotalTime() -  m_rf_exc->getDuration());
        deadtime_5 = t5 - ((1 - asym_factor) * m_vap_asym5.getDuration() + m_vaporsp_5.getTotalTime() + 0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        std::cout << "deadtime_5: " << deadtime_5 << std::endl;
		if ( deadtime_5 < 0 )
		{ 
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t5 = %d us cannot be realized;\n"
                        "deadtime_5 %d",
                        ptModule, t5, deadtime_5);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
    }

    if(WStechnique == 5){
        std::cout<<"calculating VAPOR asym deadtime"<<std::endl;
		deadtime_1 = t1 - ((1-asym_factor) *  m_vap_asym1.getDuration() + asym_factor*m_vap_asym2.getDuration() + m_vaporsp_1.getTotalTime() );
		std::cout<<"deadtime_1: "<< deadtime_1 <<std::endl;
		if ( deadtime_1 < 0 )
		{ 
			    std::cout<<"HEHE32: "<<std::endl;
			    if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t1 = %d us cannot be realized;\n"
                        "deadtime_1 %d",
                        ptModule, t1, deadtime_1);
			    }  
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31: "<<std::endl;
		deadtime_2 = t2 - ((1-asym_factor) *  m_vap_asym2.getDuration() + asym_factor*m_vap_asym3.getDuration() + m_vaporsp_2.getTotalTime() );
		if ( deadtime_2 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t2 = %d us cannot be realized;\n"
                    "deadtime_2 %d",
                    ptModule, t2, deadtime_2);
			}
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
		std::cout<<"HEHE31111: "<<std::endl;
		deadtime_3 = t3 - ((1-asym_factor)*m_vap_asym3.getDuration() + asym_factor*m_vap_asym4.getDuration() + m_vaporsp_3.getTotalTime() );
		if ( deadtime_3 < 0 )
		{ 
			  if( !(rSeqLim.isContextPrepForBinarySearch()) )
              {
				SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "t3 = %d us cannot be realized;\n"
                    "deadtime_3 %d",
                    ptModule, t3, deadtime_3);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}

        deadtime_4 = t4 - ((1 - asym_factor) * m_vap_asym4.getDuration() + 0.5 * m_rf_exc->getDuration() + m_vaporsp_4.getTotalTime() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
		if ( deadtime_4 < 0 )
		{ 
			if( !(rSeqLim.isContextPrepForBinarySearch()) )
                {
                    SEQ_TRACE_WARN.print(
                        "NEVER HAPPEN Warning from %s:\n"
                        "t6 = %d us cannot be realized;\n"
                        "deadtime_6 %d",
                        ptModule, t4, deadtime_4);
			    }
			   return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
		}
    }

    if (WStechnique == 1){ // CF VAPOR
        std::cout<<"UGHHH VAPOR PUHLEASEEE1"<<std::endl;
        SEQ_TRACE_WARN.print("prepping excit delay");
        if( m_rf_exc->getDuration() > m_rf_vapor8.getDuration() )
        { // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
              // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
            // #ifdef _DVP_DEBUG
            SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
                  "\npreceeding water suppr. pulse VAPOR(dur. %d us).\n",
                  m_rf_exc->getDuration(), m_rf_vapor8.getDuration() );

            // #endif
            return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }
        else{ // the usual case that the excit. pulse is shorter than the wat. sup. pulse
                // ... use the same spoil duration l as before, but compute m_lexcit_delay
                m_lexcit_delay = (long)(.5 + t8 - (m_vaporsp_8.getTotalTime() + .5*(m_rf_vapor8.getDuration() + m_rf_exc->getDuration()) +
                      (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
                if( m_lexcit_delay < 0 )
                      m_lexcit_delay = 0;
                m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
                SEQ_TRACE_WARN.print("m_excit_delay = %ld", m_lexcit_delay);
                std::cout<<"m_lexcit_delay VAPOR:"<<m_lexcit_delay<<std::endl;
        }
    }

    if (WStechnique == 3 || WStechnique == 4 || WStechnique == 6) // CF VAPOR asym
    { 
        std::cout<<"UGHHH VAPOR PUHLEASEEE1"<<std::endl;
        if( m_rf_exc->getDuration() > m_vap_asym8.getDuration() )
        { // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
              // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
            // #ifdef _DVP_DEBUG
            SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
                  "\npreceeding water suppr. pulse VAPOR asym(dur. %d us).\n",
                  m_rf_exc->getDuration(), m_vap_asym8.getDuration() );

            // #endif
            return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }
        else
        { // the usual case that the excit. pulse is shorter than the wat. sup. pulse
                // ... use the same spoil duration l as before, but compute m_lexcit_delay
                m_lexcit_delay = (long)(.5 + t8 - (m_vaporsp_8.getTotalTime() + (1-asym_factor)*m_vap_asym8.getDuration() + 0.5*m_rf_exc->getDuration() +
                      (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
                if( m_lexcit_delay < 0 )
                      m_lexcit_delay = 0;
                m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
                SEQ_TRACE_WARN.print("m_excit_delay = %ld", m_lexcit_delay);
                std::cout<<"m_lexcit_delay VAPOR asym:"<<m_lexcit_delay<<std::endl;
        }
    }

    if (WStechnique == 9){
        if( m_rf_exc->getDuration() > m_vap_asym5.getDuration() )
        { // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
              // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
            // #ifdef _DVP_DEBUG
            SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
                  "\npreceeding water suppr. pulse VAPOR asym(dur. %d us).\n",
                  m_rf_exc->getDuration(), m_vap_asym5.getDuration() );

            // #endif
            return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }
        else
        { // the usual case that the excit. pulse is shorter than the wat. sup. pulse
                // ... use the same spoil duration l as before, but compute m_lexcit_delay
                m_lexcit_delay = (long)(.5 + t5 - (m_vaporsp_5.getTotalTime() + (1-asym_factor)*m_vap_asym5.getDuration() + 0.5*m_rf_exc->getDuration() +
                      (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
                if( m_lexcit_delay < 0 )
                      m_lexcit_delay = 0;
                m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME; // USE DEFAULT ROUND UP FUNCTION - LOOK INTO THIS CF
                std::cout<<"m_lexcit_delay VAPOR asym:"<<m_lexcit_delay<<std::endl;
        }
    }

    if (WStechnique == 5){
        if( m_rf_exc->getDuration() > m_vap_asym4.getDuration() )
        { // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
              // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
            // #ifdef _DVP_DEBUG
            SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
                  "\npreceeding water suppr. pulse VAPOR asym(dur. %d us).\n",
                  m_rf_exc->getDuration(), m_vap_asym4.getDuration() );

            // #endif
            return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }
        else
        { // the usual case that the excit. pulse is shorter than the wats. sup. pulse
                // ... use the same spoil duration l as before, but compute m_lexcit_delay
                m_lexcit_delay = (long)(.5 + t4 - (m_vaporsp_4.getTotalTime() + (1-asym_factor)*m_vap_asym4.getDuration() + 0.5*m_rf_exc->getDuration() +
                      (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
                if( m_lexcit_delay < 0 )
                      m_lexcit_delay = 0;
                m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
                std::cout<<"m_lexcit_delay VAPOR asym:"<<m_lexcit_delay<<std::endl;
        }
    }

    // CF HGWS

	if (WStechnique == 7)
    { 
        SEQ_TRACE_WARN.print("HG_7");
        std::cout<<"calculating VAPOR asym deadtime"<<std::endl;
        HG_t1 = 58200;
        HG_t2 = 58200;
        HG_t3 = 36800;
        HG_t4 = 39100;
        HG_t5 = 49200;
        HG_deadtime_1 = HG_t1 - ((1-asym_factor)*m_HG1.getDuration() + asym_factor*m_HG2.getDuration() + m_HGsp_1.getTotalTime() );
        if ( HG_deadtime_1 < 0 )
        { 
            if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "HG_t1 = %d us cannot be realized;\n"
                    "HG_deadtime_1 %d",
                    ptModule, HG_t1, HG_deadtime_1); 
            }
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }
        SEQ_TRACE_WARN.print("HG_10");

        HG_deadtime_2 = HG_t2 - ((1-asym_factor)*m_HG2.getDuration() + asym_factor*m_HG3.getDuration() + m_HGsp_2.getTotalTime() );
        if ( HG_deadtime_2 < 0 )
        { 
            if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "HG_t2 = %d us cannot be realized;\n"
                    "HG_deadtime_2 %d",
                    ptModule, HG_t2, HG_deadtime_2);  
            }
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }

        SEQ_TRACE_WARN.print("HG_15");

        HG_deadtime_3 = HG_t3 - ((1-asym_factor)*m_HG3.getDuration() + asym_factor*m_HG4.getDuration() + m_HGsp_3.getTotalTime() );
        if ( HG_deadtime_3 < 0 )
        { 
            if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "HG_t3 = %d us cannot be realized;\n"
                    "HG_deadtime_3 %d",
                    ptModule, HG_t3, HG_deadtime_3); 
            }
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }

        SEQ_TRACE_WARN.print("HG_16");

        HG_deadtime_4 = HG_t4 - ((1-asym_factor)*m_HG4.getDuration() + asym_factor*m_HG5.getDuration() + m_HGsp_4.getTotalTime() );
        if ( HG_deadtime_4 < 0 )
        { 
            if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "HG_t4 = %d us cannot be realized;\n"
                    "HG_deadtime_4 %d",
                    ptModule, HG_t4, HG_deadtime_4); 
            }
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }

        SEQ_TRACE_WARN.print("HG_17");
        // SEQ_TRACE_WARN.print("grad_exc get ramp %f", m_grad_exc->getRampUpTime());
        SEQ_TRACE_WARN.print("rf_exc get duration %f", m_rf_exc->getDuration());

        HG_deadtime_5 = HG_t5 - ((1-asym_factor)*m_HG5.getDuration() + 0.5*m_rf_exc->getDuration() + m_HGsp_5.getTotalTime() + (m_grad_exc->getDuration() -m_rf_exc->getDuration() ) );
        std::cout<<"HG_deadtime_5: "<< HG_deadtime_5<< std::endl;
        if ( HG_deadtime_5 < 0 )
        { 
            if( !(rSeqLim.isContextPrepForBinarySearch()) )
            {
                SEQ_TRACE_WARN.print(
                    "NEVER HAPPEN Warning from %s:\n"
                    "HG_t5 = %d us cannot be realized;\n"
                    "HG_deadtime_5 %d",
                    ptModule, HG_t5, HG_deadtime_5); 
            }
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
        }

        SEQ_TRACE_WARN.print("HG_13");

        if( m_rf_exc->getDuration() > m_HG5.getDuration() )
            { // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
                    // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
                // #ifdef _DVP_DEBUG
                SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
                        "\npreceeding water suppr. pulse HGWS(dur. %d us).\n",
                        m_rf_exc->getDuration(), m_HG5.getDuration() );

                // #endif
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
            }
        else{ // the usual case that the excit. pulse is shorter than the wat. sup. pulse
                    // ... use the same spoil duration l as before, but compute m_lexcit_delay
                    m_lexcit_delay = (long)(.5 + HG_t5 - (m_HGsp_5.getTotalTime() + (1-asym_factor)*m_HG5.getDuration() + 0.5*m_rf_exc->getDuration() +
                            (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
                    if( m_lexcit_delay < 0 )
                            m_lexcit_delay = 0;
                    m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
                    std::cout<<"m_lexcit_delay HGWS:"<<m_lexcit_delay<<std::endl;

            }
            SEQ_TRACE_WARN.print("HG_11");
    }

    // CF FAST

    if (WStechnique == 2)
    {
        m_fastsp_dur_1_3 = fast_t1_3 - (.5 * (m_rf_fast1.getDuration() + m_rf_fast2.getDuration() ) + m_fastSpRamp);
        m_fastsp_dur_1_3 = (m_fastsp_dur_1_3/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
        m_fastsp_1_3amp = 1000. * FASTgradmoment_1_3 / (double) m_fastsp_dur_1_3; 

        m_fastsp_dur_4 = fast_t4 - (.5 * (m_rf_fast4.getDuration() + m_rf_fast5.getDuration() ) + m_fastSpRamp);
        m_fastsp_dur_4 = (m_fastsp_dur_4/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
        m_fastsp_4amp = 1000. * FASTgradmoment_4 / (double) m_fastsp_dur_4;

        m_fastsp_dur_5 = fast_t5 - (.5 * (m_rf_fast5.getDuration() + m_rf_fast5.getDuration() ) + m_fastSpRamp);
        m_fastsp_dur_5 = (m_fastsp_dur_5/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
        m_fastsp_5amp = 1000. * FASTgradmoment_5 / (double) m_fastsp_dur_5;

        if( m_rf_exc->getDuration() > m_rf_fast5.getDuration() )
            { // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
                    // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
                // #ifdef _DVP_DEBUG
                SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
                        "\npreceeding water suppr. pulse VAPOR(dur. %d us).\n",
                        m_rf_exc->getDuration(), m_rf_fast5.getDuration() );

                // #endif
                return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
            }
        else
            { // the usual case that the excit. pulse is shorter than the wat. sup. pulse
                    // ... use the same spoil duration l as before, but compute m_lexcit_delay
                    m_lexcit_delay = (long)(.5 + fast_t5 - (m_fastsp_dur_5 + .5*(m_rf_fast5.getDuration() + m_rf_exc->getDuration()) +
                            (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
                    if( m_lexcit_delay < 0 )
                            m_lexcit_delay = 0;
                    m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
            }
    }

    if(WStechnique == 8)
    {
        tau = 60000; // delay between water suppression pulses
		tau3 =60000; // delay between water suppression pulse 3 and excitation
        wsspgradmoment = 168;
        ramptime = 200;

        // the water suppression pulses or the excitation pulse must not be longer than tau

        // compute duration to fill intervall between RF-pulses with the spoiler gradient
        l = tau - (.5 * ( m_rf_ws1.getDuration() + m_rf_ws2.getDuration() ) + ramptime );
        l = (l/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
        d = 1000. * wsspgradmoment / (double) l; // d = gradient amplitude

        if( m_rf_exc->getDuration() > m_rf_ws3.getDuration() )
			{ // in the unlikeley case that the excit. pulse is longer than the wat. sup. pulse
				  // starting with VA15A and variable duration suppression pulses, this NEVER HAPPEN case is not any more supported
				// #ifdef _DVP_DEBUG
				SEQ_TRACE_DEBUG.print("\nfSEQPrep(): the excitation pulse (dur. %d us) must NOT be longer than the "
					  "\npreceeding water suppr. pulse (dur. %d us).\n",
					  m_rf_exc->getDuration(), m_rf_ws3.getDuration() );

				// #endif
				return MRI_SEQ_SEQU_SEQ_NOT_PREPARED;
			}
			else{ // the usual case that the excit. pulse is shorter than the wat. sup. pulse
					// ... use the same spoil duration l as before, but compute m_lexcit_delay
					m_lexcit_delay = (long)(.5 + tau3 - (l + .5*(m_rf_ws3.getDuration() + m_rf_exc->getDuration()) +
						  (m_grad_exc->getDuration() - m_rf_exc->getDuration()) ));
					if( m_lexcit_delay < 0 )
						  m_lexcit_delay = 0;
					m_lexcit_delay = (m_lexcit_delay/GRAD_RASTER_TIME)*GRAD_RASTER_TIME;
			  }
    }
    
    

    // // might need this later:

    if (WStechnique == 8){
        m_lSBBDurationPerRequest_us = 2 * tau + tau3 + 0.5 * m_rf_ws1.getDuration() - (0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration())); // rounding up a bit
        std::cout<<"h2osup_dur_WETcf: "<<m_lSBBDurationPerRequest_us<<std::endl;
    }
    else if(WStechnique == 1)
    {
        
        // m_lSBBDurationPerRequest_us = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + (0.5*m_rf_vapor1.getDuration() + 0.5*m_rf_vapor8.getDuration());
        m_lSBBDurationPerRequest_us
            = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + .5 * m_rf_vapor1.getDuration()
              - (0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        SEQ_TRACE_WARN.print("sbbduration = %ld", m_lSBBDurationPerRequest_us);
        std::cout<<"h2osup_dur_vapor: "<<m_lSBBDurationPerRequest_us<<std::endl;
        std::cout<<"UGHHH VAPOR PUHLEASEEE5"<<std::endl;
    }
    else if(WStechnique == 2)
    {// CF fast
        m_lSBBDurationPerRequest_us
            = fast_t1_3 + fast_t4 + fast_t5 + 0.5 * m_rf_fast1.getDuration()
              - (0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        std::cout<<"h2osup_dur_fast: "<<m_lSBBDurationPerRequest_us<<std::endl;
    }
    else if(WStechnique == 7)
    { // CF HGWS
        SEQ_TRACE_WARN.print("HG_9");
        m_lSBBDurationPerRequest_us = HG_t1 + HG_t2 + HG_t3 + HG_t4 + HG_t5 + asym_factor * m_HG1.getDuration() - ( 0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        std::cout<<"h2osup_dur_HGWS: "<<m_lSBBDurationPerRequest_us<<std::endl;
    }
    else if(WStechnique == 3 || WStechnique == 4 || WStechnique == 6)
    {
        m_lSBBDurationPerRequest_us = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + asym_factor*m_vap_asym1.getDuration() - (0.5*m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        // m_lSBBDurationPerRequest_us
           // = t1 + t2 + t3 + t4 + t5 + t6 + t7 + t8 + m_vap_asym1.getDuration();
        SEQ_TRACE_WARN.print("sbbduration = %ld", m_lSBBDurationPerRequest_us);
        std::cout<<"h2osup_dur_vapor asym: "<<m_lSBBDurationPerRequest_us<<std::endl;
        std::cout<<"UGHHH VAPOR PUHLEASEEE5"<<std::endl;
    }
    else if(WStechnique == 9){
        // m_lSBBDurationPerRequest_us = t1 + t2 + t3 + t4 + t5 + asym_factor*m_vap_asym1.getDuration() - (0.5*m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        m_lSBBDurationPerRequest_us = t1 + t2 + t3 + t4 + t5 + asym_factor * m_vap_asym1.getDuration() - (0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        std::cout<<"h2osup_dur_vapor asym 5pulses: "<<m_lSBBDurationPerRequest_us <<std::endl;
    }
    else if(WStechnique == 5){
        m_lSBBDurationPerRequest_us
            = t1 + t2 + t3 + t4 + asym_factor * m_vap_asym1.getDuration() - (0.5 * m_rf_exc->getDuration() + (m_grad_exc->getDuration() - m_rf_exc->getDuration()));
        std::cout<<"h2osup_dur_vapor asym 4pulses 50ms: "<<m_lSBBDurationPerRequest_us<<std::endl;
    }
    else {
        // m_lSBBDurationPerRequest_us = 0;
        return false;
    }

    setPrepared();
    return true;


}

bool /*SEQ_NAMESPACE::*/SeqBuildBlockWatSupVAPOR_CF::run (MrProt &rMrProt, SeqLim & rSeqLim, MrProtocolData::SeqExpo &rSeqExpo, sSLICE_POS* pSLC) // add wip param
{
    // if (!isPrepared())
    // return true;
    // if (!SeqBuildBlockWatSup::run(rMrProt, rSeqLim, rSeqExpo, pSLC))
    // return false;

    // add the fRTEI stuff here
    fRTEBInit(m_fov->getROT_MATRIX(), true);
    // fRTEBInit(sNewRotationMatrix, true);

    lT=0;
	// lT_1 = 0;

    if( m_lis_watsup) // define this somewhere
    {
        if( m_lis_watsupRF )
        {
			if(WStechnique == 8)
            {
				 fRTEI(lT+= 0, &m_ph_s_ws, &m_rf_ws1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_ws1.getDuration(),  &m_ph_n_ws, 0, /*A*/ 0, 0,0,&m_wssp_ph,0);
				 fRTEI(lT+= (m_wssp_ph.getDuration()+m_wssp_ph.getRampDownTime()), &m_ph_s_ws, &m_rf_ws2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_ws2.getDuration(),  &m_ph_n_ws, 0, /*A*/ 0, 0, 0,&m_wssp_ro,0);
				 fRTEI(lT+= (m_wssp_ro.getDuration()+m_wssp_ro.getRampDownTime()), &m_ph_s_ws, &m_rf_ws3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_ws3.getDuration(),  &m_ph_n_ws, 0, /*A*/ 0, 0, 0,&m_wssp_sl, 0);
				 fRTEI(lT+= (m_wssp_sl.getTotalTime()+m_lexcit_delay),  0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH chess cf PUHLEASEEEwhat"<<std::endl;
			}
			else if(WStechnique == 1)
            {

			 // CF VAPOR
                SEQ_TRACE_WARN.print("running ");
				 fRTEI(lT+= 0, &m_ph_s_vapor1, &m_rf_vapor1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor1.getDuration(),  &m_ph_n_vapor1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_vapor2, &m_rf_vapor2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor2.getDuration(),  &m_ph_n_vapor2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_vapor3, &m_rf_vapor3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor3.getDuration(),  &m_ph_n_vapor3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_vapor4, &m_rf_vapor4,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor4.getDuration(),  &m_ph_n_vapor4, 0, /*A*/ 0, 0, &m_vaporsp_4,0,0);
				 fRTEI(lT+= (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime()+ deadtime_4), &m_ph_s_vapor5, &m_rf_vapor5,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor5.getDuration(),  &m_ph_n_vapor5, 0, /*A*/ 0, &m_vaporsp_5, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_5.getDuration()+m_vaporsp_5.getRampDownTime()+ deadtime_5), &m_ph_s_vapor6, &m_rf_vapor6,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor6.getDuration(),  &m_ph_n_vapor6, 0, /*A*/ 0, 0, 0,&m_vaporsp_6,0);
				 fRTEI(lT+= (m_vaporsp_6.getDuration()+m_vaporsp_6.getRampDownTime()+ deadtime_6), &m_ph_s_vapor7, &m_rf_vapor7,/*A*/ 0,0,0,0,0); // CF change this to add one more pulse
				 fRTEI( lT+= m_rf_vapor7.getDuration(),  &m_ph_n_vapor7, 0, /*A*/ 0, 0, &m_vaporsp_7,0,0);
				 fRTEI(lT+= (m_vaporsp_7.getDuration()+m_vaporsp_7.getRampDownTime()+ deadtime_7), &m_ph_s_vapor8, &m_rf_vapor8,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor8.getDuration(),  &m_ph_n_vapor8, 0, /*A*/ 0, &m_vaporsp_8, 0,&m_vaporsp_8,0);
				 fRTEI(lT+= (m_vaporsp_8.getDuration() + m_vaporsp_8.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
                 SEQ_TRACE_WARN.print("running");
				 std::cout<<"UGHHH VAPOR PUHLEASEEE4"<<std::endl;
			}
			else if(WStechnique == 2)
            {// FAST
				 fRTEI(lT+= 0, &m_ph_s_fast1, &m_rf_fast1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast1.getDuration(),  &m_ph_n_fast1, 0, /*A*/ 0, 0,&m_fastsp_1,0,0);
				 fRTEI(lT+= (m_fastsp_1.getDuration()+m_fastsp_1.getRampDownTime()), &m_ph_s_fast2, &m_rf_fast2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast2.getDuration(),  &m_ph_n_fast2, 0, /*A*/ 0, &m_fastsp_2, 0,0,0);
				 fRTEI(lT+= (m_fastsp_2.getDuration()+m_fastsp_2.getRampDownTime()), &m_ph_s_fast3, &m_rf_fast3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast3.getDuration(),  &m_ph_n_vapor3, 0, /*A*/ 0, 0, 0,&m_fastsp_3,0);
				 fRTEI(lT+= (m_fastsp_3.getDuration()+m_fastsp_3.getRampDownTime()), &m_ph_s_fast4, &m_rf_fast4,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast4.getDuration(),  &m_ph_n_fast4, 0, /*A*/ 0, 0, &m_fastsp_4,0,0);
				 fRTEI(lT+= (m_fastsp_4.getDuration()+m_fastsp_4.getRampDownTime()), &m_ph_s_fast5, &m_rf_fast5,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast5.getDuration(),  &m_ph_n_fast5, 0, /*A*/ 0, 0, &m_fastsp_5,&m_fastsp_5,0);
				 fRTEI(lT+= (m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH FAST PUHLEASEEE"<<std::endl;
			}
			else if(WStechnique == 7)
            { // HGWS
				 fRTEI(lT+= 0, &m_ph_s_HG1, &m_HG1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG1.getDuration(),  &m_ph_n_HG1, 0, /*A*/ 0, 0,&m_HGsp_1,0,0);
				 fRTEI(lT+= (m_HGsp_1.getDuration()+m_HGsp_1.getRampDownTime() + HG_deadtime_1), &m_ph_s_HG2, &m_HG2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG2.getDuration(),  &m_ph_n_HG2, 0, /*A*/ 0, &m_HGsp_2, 0,0,0);
				 fRTEI(lT+= (m_HGsp_2.getDuration()+m_HGsp_2.getRampDownTime() + HG_deadtime_2), &m_ph_s_HG3, &m_HG3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG3.getDuration(),  &m_ph_n_HG3, 0, /*A*/ 0, 0, 0,&m_HGsp_3,0);
				 fRTEI(lT+= (m_HGsp_3.getDuration()+m_HGsp_3.getRampDownTime() + HG_deadtime_3), &m_ph_s_HG4, &m_HG4,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG4.getDuration(),  &m_ph_n_HG4, 0, /*A*/ 0, 0, &m_HGsp_4,0,0);
				 fRTEI(lT+= (m_HGsp_4.getDuration()+m_HGsp_4.getRampDownTime() + HG_deadtime_4), &m_ph_s_HG5, &m_HG5,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG5.getDuration(),  &m_ph_n_HG5, 0, /*A*/ 0, &m_HGsp_5, 0,0,0);
				 fRTEI(lT+= (m_HGsp_5.getDuration() + m_HGsp_5.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
			}
			else if(WStechnique == 3 || WStechnique == 4 || WStechnique == 6)
            {
				 fRTEI(lT+= 0, &m_ph_s_asym1, &m_vap_asym1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym1.getDuration(),  &m_ph_n_asym1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_asym2, &m_vap_asym2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym2.getDuration(),  &m_ph_n_asym2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_asym3, &m_vap_asym3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym3.getDuration(),  &m_ph_n_asym3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_asym4, &m_vap_asym4,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym4.getDuration(),  &m_ph_n_asym4, 0, /*A*/ 0, 0, &m_vaporsp_4,0,0);
				 fRTEI(lT+= (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime()+ deadtime_4), &m_ph_s_asym5, &m_vap_asym5,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym5.getDuration(),  &m_ph_n_asym5, 0, /*A*/ 0, &m_vaporsp_5, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_5.getDuration()+m_vaporsp_5.getRampDownTime()+ deadtime_5), &m_ph_s_asym6, &m_vap_asym6,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym6.getDuration(),  &m_ph_n_asym6, 0, /*A*/ 0, 0, 0,&m_vaporsp_6,0);
				 fRTEI(lT+= (m_vaporsp_6.getDuration()+m_vaporsp_6.getRampDownTime()+ deadtime_6), &m_ph_s_asym7, &m_vap_asym7,/*A*/ 0,0,0,0,0); // CF change this to add one more pulse
				 fRTEI( lT+= m_vap_asym7.getDuration(),  &m_ph_n_asym7, 0, /*A*/ 0, 0, &m_vaporsp_7,0,0);
				 fRTEI(lT+= (m_vaporsp_7.getDuration()+m_vaporsp_7.getRampDownTime()+ deadtime_7), &m_ph_s_asym8, &m_vap_asym8,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym8.getDuration(),  &m_ph_n_asym8, 0, /*A*/ 0, &m_vaporsp_8, 0,&m_vaporsp_8,0);
				 fRTEI(lT+= (m_vaporsp_8.getDuration()+m_vaporsp_8.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH VAPOR PUHLEASEEE4"<<std::endl;
			}
            else if(WStechnique == 9){
                 fRTEI(lT+= 0, &m_ph_s_asym1, &m_vap_asym1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym1.getDuration(),  &m_ph_n_asym1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_asym2, &m_vap_asym2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym2.getDuration(),  &m_ph_n_asym2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_asym3, &m_vap_asym3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym3.getDuration(),  &m_ph_n_asym3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_asym4, &m_vap_asym4,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym4.getDuration(),  &m_ph_n_asym4, 0, /*A*/ 0, 0, &m_vaporsp_4,0,0);
				 fRTEI(lT+= (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime()+ deadtime_4), &m_ph_s_asym5, &m_vap_asym5,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym5.getDuration(),  &m_ph_n_asym5, 0, /*A*/ 0, &m_vaporsp_5, 0,&m_vaporsp_5,0);
                 fRTEI(lT+= (m_vaporsp_5.getDuration()+m_vaporsp_5.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
                 std::cout << "m_lexcit_delay = " << m_lexcit_delay << std::endl;
            }
            else if(WStechnique == 5){

                 UTRACE(Notice, 0, "WS 5 3");

                 fRTEI(lT+= 0, &m_ph_s_asym1, &m_vap_asym1,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym1.getDuration(),  &m_ph_n_asym1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_asym2, &m_vap_asym2,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym2.getDuration(),  &m_ph_n_asym2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_asym3, &m_vap_asym3,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym3.getDuration(),  &m_ph_n_asym3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_asym4, &m_vap_asym4,/*A*/ 0,0,0,0,0);
                 fRTEI(lT += m_vap_asym4.getDuration(), &m_ph_n_asym4, 0, /*A*/ 0, &m_vaporsp_4, 0, &m_vaporsp_4, 0);
                 fRTEI(lT += (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime() + m_lexcit_delay), 0, 0, /*A*/ 0, 0, 0, 0, 0);

                 UTRACE(Notice, 0, "WS 5 4");

            }
        }

        // Reference Scan Mode: WET Spoiler-Gradients are switched on RF is switched Off
        if(rMrProt.preparationPulses().getlFatWaterContrast() == FatWaterContrast_WaterSuppresionRFOff)
        {
			if(WStechnique == 8)
            {
				 fRTEI(lT+= 0, &m_ph_s_ws, 0    ,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_ws1.getDuration(),  &m_ph_n_ws, 0, /*A*/ 0, 0,0,&m_wssp_ph,0);
				 fRTEI(lT+= (m_wssp_ph.getDuration()+m_wssp_ph.getRampDownTime()), &m_ph_s_ws, 0   ,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_ws2.getDuration(),  &m_ph_n_ws, 0, /*A*/ 0, 0, 0,&m_wssp_ro,0);
				 fRTEI(lT+= (m_wssp_ro.getDuration()+m_wssp_ro.getRampDownTime()), &m_ph_s_ws, 0   ,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_ws3.getDuration(),  &m_ph_n_ws, 0, /*A*/ 0, 0, 0,&m_wssp_sl, 0);
				 fRTEI(lT+= (m_wssp_sl.getTotalTime()+m_lexcit_delay),  0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH chess cf PUHLEASEEEhuhhhhh"<<std::endl;
			}
			else if(WStechnique == 1)
            {
			 // CF VAPOR
                SEQ_TRACE_WARN.print("running");
				 fRTEI(lT+= 0, &m_ph_s_vapor1, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor1.getDuration(),  &m_ph_n_vapor1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_vapor2, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor2.getDuration(),  &m_ph_n_vapor2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_vapor3, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor3.getDuration(),  &m_ph_n_vapor3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_vapor4, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor4.getDuration(),  &m_ph_n_vapor4, 0, /*A*/ 0, 0, &m_vaporsp_4,0,0);
				 fRTEI(lT+= (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime()+ deadtime_4), &m_ph_s_vapor5, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor5.getDuration(),  &m_ph_n_vapor5, 0, /*A*/ 0, &m_vaporsp_5, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_5.getDuration()+m_vaporsp_5.getRampDownTime()+ deadtime_5), &m_ph_s_vapor6, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor6.getDuration(),  &m_ph_n_vapor6, 0, /*A*/ 0, 0, 0,&m_vaporsp_6,0);
				 fRTEI(lT+= (m_vaporsp_6.getDuration()+m_vaporsp_6.getRampDownTime()+ deadtime_6), &m_ph_s_vapor7, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor7.getDuration(),  &m_ph_n_vapor7, 0, /*A*/ 0, 0, &m_vaporsp_7,0,0);
				 fRTEI(lT+= (m_vaporsp_7.getDuration()+m_vaporsp_7.getRampDownTime()+ deadtime_7), &m_ph_s_vapor8, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_vapor8.getDuration(),  &m_ph_n_vapor8, 0, /*A*/ 0, &m_vaporsp_8,0,&m_vaporsp_8,0);
				 fRTEI(lT+= (m_vaporsp_8.getDuration() + m_vaporsp_8.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
                 SEQ_TRACE_WARN.print("running");
				 std::cout<<"UGHHH VAPOR PUHLEASEEE3"<<std::endl;
			}
			else if(WStechnique == 2)
            {// CF FAST
				 fRTEI(lT+= 0, &m_ph_s_fast1, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast1.getDuration(),  &m_ph_n_fast1, 0, /*A*/ 0, 0,&m_fastsp_1,0,0);
				 fRTEI(lT+= (m_fastsp_1.getDuration()+m_fastsp_1.getRampDownTime()), &m_ph_s_fast2, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast2.getDuration(),  &m_ph_n_fast2, 0, /*A*/ 0, &m_fastsp_2, 0,0,0);
				 fRTEI(lT+= (m_fastsp_2.getDuration()+m_fastsp_2.getRampDownTime()), &m_ph_s_fast3, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast3.getDuration(),  &m_ph_n_fast3, 0, /*A*/ 0, 0, 0,&m_fastsp_3,0);
				 fRTEI(lT+= (m_fastsp_3.getDuration()+m_fastsp_3.getRampDownTime()), &m_ph_s_fast4, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast4.getDuration(),  &m_ph_n_fast4, 0, /*A*/ 0, 0, &m_fastsp_4,0,0);
				 fRTEI(lT+= (m_fastsp_4.getDuration()+m_fastsp_4.getRampDownTime()), &m_ph_s_fast5, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_rf_fast5.getDuration(),  &m_ph_n_fast5, 0, /*A*/ 0, 0, &m_fastsp_5,&m_fastsp_5,0);
				 fRTEI(lT+= (m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH FAST PUHLEASEEE"<<std::endl;
			}
			else if(WStechnique == 7)
            { // HGWS
				 fRTEI(lT+= 0, &m_ph_s_HG1, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG1.getDuration(),  &m_ph_n_HG1, 0, /*A*/ 0, 0,&m_HGsp_1,0,0);
				 fRTEI(lT+= (m_HGsp_1.getDuration()+m_HGsp_1.getRampDownTime() + HG_deadtime_1), &m_ph_s_HG2, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG2.getDuration(),  &m_ph_n_HG2, 0, /*A*/ 0, &m_HGsp_2, 0,0,0);
				 fRTEI(lT+= (m_HGsp_2.getDuration()+m_HGsp_2.getRampDownTime() + HG_deadtime_2), &m_ph_s_HG3, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG3.getDuration(),  &m_ph_n_HG3, 0, /*A*/ 0, 0, 0,&m_HGsp_3,0);
				 fRTEI(lT+= (m_HGsp_3.getDuration()+m_HGsp_3.getRampDownTime() + HG_deadtime_3), &m_ph_s_HG4, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG4.getDuration(),  &m_ph_n_HG4, 0, /*A*/ 0, 0, &m_HGsp_4,0,0);
				 fRTEI(lT+= (m_HGsp_4.getDuration()+m_HGsp_4.getRampDownTime() + HG_deadtime_4 ), &m_ph_s_HG5, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_HG5.getDuration(),  &m_ph_n_HG5, 0, /*A*/ 0, &m_HGsp_5, 0,0,0);
				 fRTEI(lT+= (m_HGsp_5.getDuration() + m_HGsp_5.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH HGWS PUHLEASEEE"<<std::endl;
			}
			else if(WStechnique == 3 || WStechnique == 4 || WStechnique == 6)
            {
				 fRTEI(lT+= 0, &m_ph_s_asym1, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym1.getDuration(),  &m_ph_n_asym1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_asym2, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym2.getDuration(),  &m_ph_n_asym2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_asym3, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym3.getDuration(),  &m_ph_n_asym3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_asym4, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym4.getDuration(),  &m_ph_n_asym4, 0, /*A*/ 0, 0, &m_vaporsp_4,0,0);
				 fRTEI(lT+= (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime()+ deadtime_4), &m_ph_s_asym5, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym5.getDuration(),  &m_ph_n_asym5, 0, /*A*/ 0, &m_vaporsp_5, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_5.getDuration()+m_vaporsp_5.getRampDownTime()+ deadtime_5), &m_ph_s_asym6, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym6.getDuration(),  &m_ph_n_asym6, 0, /*A*/ 0, 0, 0,&m_vaporsp_6,0);
				 fRTEI(lT+= (m_vaporsp_6.getDuration()+m_vaporsp_6.getRampDownTime()+ deadtime_6), &m_ph_s_asym7, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym7.getDuration(),  &m_ph_n_asym7, 0, /*A*/ 0, 0, &m_vaporsp_7,0,0);
				 fRTEI(lT+= (m_vaporsp_7.getDuration()+m_vaporsp_7.getRampDownTime()+ deadtime_7), &m_ph_s_asym8, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym8.getDuration(),  &m_ph_n_asym8, 0, /*A*/ 0, &m_vaporsp_8, 0,&m_vaporsp_8,0);
				 fRTEI(lT+= (m_vaporsp_8.getDuration()+m_vaporsp_8.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
				 std::cout<<"UGHHH VAPOR asym PUHLEASEEE3"<<std::endl;
			}
            else if(WStechnique == 9){
                 fRTEI(lT+= 0, &m_ph_s_asym1, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym1.getDuration(),  &m_ph_n_asym1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_asym2, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym2.getDuration(),  &m_ph_n_asym2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_asym3, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym3.getDuration(),  &m_ph_n_asym3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_asym4, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym4.getDuration(),  &m_ph_n_asym4, 0, /*A*/ 0, 0, &m_vaporsp_4,0,0);
				 fRTEI(lT+= (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime()+ deadtime_4), &m_ph_s_asym5, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym5.getDuration(),  &m_ph_n_asym5, 0, /*A*/ 0, &m_vaporsp_5, 0,&m_vaporsp_5,0);
                 fRTEI(lT+= (m_vaporsp_5.getDuration()+m_vaporsp_5.getRampDownTime() + m_lexcit_delay), 0, 0,/*A*/ 0,0,0,0,0);
            }
            else if(WStechnique == 5){

                UTRACE(Notice, 0, "WS 5 1");

                 fRTEI(lT+= 0, &m_ph_s_asym1, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym1.getDuration(),  &m_ph_n_asym1, 0, /*A*/ 0, 0,&m_vaporsp_1,0,0);
				 fRTEI(lT+= (m_vaporsp_1.getDuration()+m_vaporsp_1.getRampDownTime()+ deadtime_1), &m_ph_s_asym2, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym2.getDuration(),  &m_ph_n_asym2, 0, /*A*/ 0, &m_vaporsp_2, 0,0,0);
				 fRTEI(lT+= (m_vaporsp_2.getDuration()+m_vaporsp_2.getRampDownTime()+ deadtime_2), &m_ph_s_asym3, 0,/*A*/ 0,0,0,0,0);
				 fRTEI( lT+= m_vap_asym3.getDuration(),  &m_ph_n_asym3, 0, /*A*/ 0, 0, 0,&m_vaporsp_3,0);
				 fRTEI(lT+= (m_vaporsp_3.getDuration()+m_vaporsp_3.getRampDownTime()+ deadtime_3), &m_ph_s_asym4, 0,/*A*/ 0,0,0,0,0);
                 fRTEI(lT += m_vap_asym4.getDuration(), &m_ph_n_asym4, 0, /*A*/ 0, &m_vaporsp_4, 0, &m_vaporsp_4, 0);
                 fRTEI(lT += (m_vaporsp_4.getDuration()+m_vaporsp_4.getRampDownTime() + m_lexcit_delay), 0, 0, /*A*/ 0, 0, 0, 0, 0);

                 UTRACE(Notice, 0, "WS 5 2");
            }
		}
    }

    // lT_1 = lT;

    fRTEBFinish();

    return true;
    
}

// #ifdef SEQ_NAMESPACE
// } // namespace SEQ_NAMESPACE
// #endif

// void /*SEQ_NAMESPACE::*/SeqBuildBlockWatSupVAPOR_CF::addToSBBList(SBBList* pSBBList)
// {
//     if (pSBBList)
    
//         pSBBList->addToSBBList(this);
    
// }

// #ifdef SEQ_NAMESPACE
// } // namespace SEQ_NAMESPACE
// #endif