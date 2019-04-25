This repository contains information about the mc weight files used in the analysis. 

| File Name     | Description                                          | Region Used | Process Names | Location if not commited | 
| ------------- | -------------                                        | ----------- | ------------- | ------------------------ |
| electron_trigger_weight/triggerEfficiency_DATA_SingleElectron.root | Electron trigger efficiency | Wen, Zee | All | - |
| met_trigger_weight/metTriggerEfficiency_mjj_vbf_zmm*.root | MET trigger efficiency in Zmm events | Zmm      | All | - |
| met_trigger_weight/metTriggerEfficiency_mjj_vbf*.root     | MET trigger efficiency in Wmn events | SR, Wmn  | All | - |
| kfactor_vjet_ewk/kFactor_ZToNuNu_pT_Mjj.root              | NLO-QCD k-factor for EWK-Z           | SR, Zmm, Zee | Z+jets EWK | - |
| kfactor_vjet_ewk/kFactor_WToLNu_pT_Mjj.root               | NLO-QCD k-factor for EWK-W           | SR, Wmn, Wen | W+jets EWK | - |
| kfactor_vjet_qcd/kfactor_24bins.root                      | NLO-QCD and EWK k-factor for W and Z+jets after monojet-like cuts | All | Z and W +jets QCD | - |
| kfactor_vjet_qcd/kfactor_VBF_zjets_v2.root                | NLO-QCD k-factor for Z+jets vs VBF selections | SR, Zmm, Zee | Z+jets QCD | - |
| kfactor_vjet_qcd/kfactor_VBF_wjets_v2.root                | NLO-QCD k-factor for W+jets vs VBF selections | SR, Wmn, Wen | W+jets QCD | - |
| qcd_datadriven_template/templates_QCD_DD.root             | Data driven QCD estimation in the VBF SR      | SR  | QCD | - |


For V+jets QCD k-factors: _vbf means derived after selections close to the cut and count one, _vbf_relaxed are derived after more inclusive selection similar to the one adopted in the shape analysis.

For the QCD data driven templates: template_QCD_SR_fromDD corresponds to the central prediction, in the "BinByBin" directory you can find the template variations due to the statistical uncertainty on the transfer factors, in the "ZJets" and "WJets" directories the alternative templates obtained after scaling the V+jets contributions in the control region.