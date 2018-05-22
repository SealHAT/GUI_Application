/* MIT License
 *
 * Copyright (c) 2018 SealHAT: Seal Heart and Activity Tracker
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef ECG_H
#define ECG_H

#ifdef __cplusplus
extern "C"
{
#endif

//libraries we used in ecg.h
//#include "max30003.h"
//#include "max30003test.h"
#include <stdbool.h>
#include <stdio.h>


/**
 * Ekg Configuration enum
 *
 * Each represents the results indicating if the configuration applied or not. 
 * Config_Failure would not result any extra influence on registers 
 */
typedef enum config_status {
	SAME_CONFIG = 0,
	CONFIG_SUCCESS = 1,
	CONFIG_FAILURE = 2
} config_status;

/**
 * ecg_change_gain
 *
 * Change cnfg_ecg register D[17:16] value to achieve the goal of adjusting gain 
 * of ecg. This allow you to input any CNFGECG_GAIN_VAL, and the func checks for
 * should any changes need to be applied if the settings already applied

 * @param CNFG_ECG_GAIN_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_change_gain(CNFGECG_GAIN_VAL vals);

/**
 * ecg_change_lowfre
 *
 * Change cnfg_ecg register D[13:12] value to achieve the goal of adjusting digital 
 * low-pass filter of ecg. This allow you to input any CNFGECG_DLPF_VAL, and the func 
 *checks for should any changes need to be applied if the settings already applied

 * @param CNFG_ECG_DLPF_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_change_lowfre(CNFGECG_DLPF_VAL vals);

/**
 * ecg_change_datarate
 *
 * Change cnfg_ecg register D[23:22] value to achieve the goal of adjusting sample 
 * rate of ecg. This allow you to input any CNFGECG_RATE_VAL, and the func checks for
 * should any changes need to be applied if the settings already applied

 * @param CNFG_ECG_RATE_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_change_datarate(CNFGECG_RATE_VAL vals);

/**
 * ecg_init()
 *
 * Initializes and starts the ekg module with the default configurations
 * (see doucumentation for default ekg config)
 *
 * @return CONFIG_SUCCESS if successful, CONFIGFAILURE if initialization fails
 */
config_status ecg_init();

/**
 * ecg_switch
 *
 * Change cnfg_gen register D[19] value to achieve the goal of adjusting switch 
 * of ecg. This allow you to input any CNFGGEN_EN_ECG_VAL, and the func checks for
 * should any changes need to be applied if the settings already applied

 * @param CNFGGEN_EN_ECG_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_switch(CNFGGEN_EN_ECG_VAL vals);

/**
 * ecg_dcloff_switch
 *
 * Change cnfg_gen register D[13:12] value to achieve the goal of enable dc 
 * lead-off detection. This allow you to choose enable dc lead-off detection 
 * or not, the func checks for should any changes need to be applied if the 
 * settings already applied

 * @param CNFGGEN_EN_DCLOFF_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_switch(CNFGGEN_EN_DCLOFF_VAL vals);

/**
 * ecg_dcloff_ipol
 *
 * Change cnfg_ecg register D[11] value to achieve the goal of change dc  
 * lead-off current polarity of ecg. This allow you to input any DCLOFF_IPOL_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_DCLOFF_IPOL_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_ipol(CNFGGEN_DCLOFF_IPOL_VAL vals);

/**
 * ecg_dcloff_imag
 *
 * Change cnfg_ecg register D[10:8] value to achieve the goal of change dc  
 * lead-off current magnitude of ecg. This allow you to input any DCLOFF_IMAG_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_DCLOFF_IMAG_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_imag(CNFGGEN_DCLOFF_IMAG_VAL vals);

/**
 * ecg_dcloff_vth
 *
 * Change cnfg_ecg register D[7:6] value to achieve the goal of change dc  
 * lead-off voltage threshold of ecg. This allow you to input any DCLOFF_VTH_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_DCLOFF_VTH_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_dcloff_vth(CNFGGEN_DCLOFF_VTH_VAL vals);

/**
 * ecg_en_rbias
 *
 * Change cnfg_ecg register D[5:4] value to achieve the goal of enable
 * resistive lead-bias mode of ecg. This allow you to input any CNFGGEN_EN_RBIAS_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_EN_RBIAS_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_rbias(CNFGGEN_EN_RBIAS_VAL vals);

/**
 * ecg_en_rbiasv
 *
 * Change cnfg_ecg register D[3:2] value to achieve the goal of change
 * resistive lead-bias mode vale of ecg. This allow you to input any CNFGGEN_RBIASV_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_RBIASV_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_rbiasv(CNFGGEN_RBIASV_VAL vals);

/**
 * ecg_en_rbiasp
 *
 * Change cnfg_ecg register D[1] value to achieve the goal of enable resistive lead-bias mode
 * on positive input of ecg. This allow you to input any CNFGGEN_RBIASV_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_RBIASP_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_rbiasp(CNFGGEN_RBIASP_VAL vals);

/**
 * ecg_en_rbiasn
 *
 * Change cnfg_ecg register D[0] value to achieve the goal of enable resistive lead-bias mode
 * on negative input of ecg. This allow you to input any CNFGGEN_RBIASN_VAL,
 * and the func checks should any changes need to be applied if the settings
 * already applied

 * @param CNFGGEN_RBIASN_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_rbiasn(CNFGGEN_RBIASN_VAL vals);

/**
 * ecg_en_dcloff_int2
 *
 * enable the dc-lead off interrupt into second interrupt pin

 * @param CNFGGEN_RBIASN_VAL(see max30003types.h)
 * @return CONFIG_SUCCESS if successful, SAME_CONFIG if setting already applied, CONFIG_FAILURE if config failed
 */
config_status ecg_en_dcloff_int2(ENINT_ENDCLOFFINT_VAL vals,ENINT_INTBTYPE_VAL type);
#ifdef __cplusplus
}
#endif
#endif
