#!/usr/bin/env python
import ROOT
import re
import array


def main(args):

    file=ROOT.TFile(args.TheoryInput,"r")

    adapt=ROOT.gROOT.GetColor(12)
    new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
    trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

    nvar=1
    variable=[args.Var]
    postfix=["_THU_ggH_Mu","_THU_ggH_Res","_THU_ggH_Mig01","_THU_ggH_Mig12","_THU_ggH_VBF2j","_THU_ggH_VBF3j","_THU_ggH_PT60","_THU_ggH_PT120","_THU_ggH_qmtop"]

    for k in range(0,nvar):

       dir_nnlops=variable[k]+"_nnlops_tautrg"
       dir_powheg=variable[k]+"_powheg_tautrg"

#       dir_nnlops=variable[k]+"_nnlops"
#       dir_powheg=variable[k]+"_powheg"

       xs_perbin=[]
       xs_perbin_unc=[]

       xs=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
       for j in range(0,5):
         
         
         xs[0]=xs[0]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)*file.Get(dir_nnlops).Get("ggH_htt125").GetEntries()/file.Get("Events").Get("ggH_htt125").GetBinContent(1)*10
         xs[0]=xs[0]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("qqH_htt125").GetEntries()/file.Get("Events").Get("qqH_htt125").GetBinContent(1)*10
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_lep_htt125").GetEntries()/file.Get("Events").Get("ggZH_lep_htt125").GetBinContent(1)*10
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_had_htt125").GetEntries()/file.Get("Events").Get("ggZH_had_htt125").GetBinContent(1)*10
         xs[0]=xs[0]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("WH_htt125").GetEntries()/file.Get("Events").Get("WH_htt125").GetBinContent(1)*10
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ZH_htt125").GetEntries()/file.Get("Events").Get("ZH_htt125").GetBinContent(1)*10
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ttH_htt125").GetEntries()/file.Get("Events").Get("ttH_htt125").GetBinContent(1)*10
         
         for z in range(0,9):
            xs[z+1]=xs[z+1]+file.Get(dir_nnlops).Get("ggH_htt125"+postfix[z]).GetBinContent(j)*file.Get(dir_nnlops).Get("ggH_htt125").GetEntries()/file.Get("Events").Get("ggH_htt125").GetBinContent(1)*10
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("qqH_htt125").GetEntries()/file.Get("Events").Get("qqH_htt125").GetBinContent(1)*10
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_lep_htt125").GetEntries()/file.Get("Events").Get("ggZH_lep_htt125").GetBinContent(1)*10
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_had_htt125").GetEntries()/file.Get("Events").Get("ggZH_had_htt125").GetBinContent(1)*10
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("WH_htt125").GetEntries()/file.Get("Events").Get("WH_htt125").GetBinContent(1)*10
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ZH_htt125").GetEntries()/file.Get("Events").Get("ZH_htt125").GetBinContent(1)*10
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ttH_htt125").GetEntries()/file.Get("Events").Get("ttH_htt125").GetBinContent(1)*10

         xs[10]=xs[10]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)*file.Get(dir_nnlops).Get("ggH_htt125").GetEntries()/file.Get("Events").Get("ggH_htt125").GetBinContent(1)*10
         xs[10]=xs[10]+file.Get(dir_powheg).Get("qqH_htt125_scale").GetBinContent(j)*file.Get(dir_powheg).Get("qqH_htt125").GetEntries()/file.Get("Events").Get("qqH_htt125").GetBinContent(1)*10
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_lep_htt125").GetEntries()/file.Get("Events").Get("ggZH_lep_htt125").GetBinContent(1)*10
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_had_htt125").GetEntries()/file.Get("Events").Get("ggZH_had_htt125").GetBinContent(1)*10
         xs[10]=xs[10]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("WH_htt125").GetEntries()/file.Get("Events").Get("WH_htt125").GetBinContent(1)*10
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ZH_htt125").GetEntries()/file.Get("Events").Get("ZH_htt125").GetBinContent(1)*10
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ttH_htt125").GetEntries()/file.Get("Events").Get("ttH_htt125").GetBinContent(1)*10

         xs[11]=xs[11]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)*file.Get(dir_nnlops).Get("ggH_htt125").GetEntries()/file.Get("Events").Get("ggH_htt125").GetBinContent(1)*10
         xs[11]=xs[11]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("qqH_htt125").GetEntries()/file.Get("Events").Get("qqH_htt125").GetBinContent(1)*10
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_lep_htt125").GetEntries()/file.Get("Events").Get("ggZH_lep_htt125").GetBinContent(1)*10
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_had_htt125").GetEntries()/file.Get("Events").Get("ggZH_had_htt125").GetBinContent(1)*10
         xs[11]=xs[11]+file.Get(dir_powheg).Get("WH_htt125_scale").GetBinContent(j)*file.Get(dir_powheg).Get("WH_htt125").GetEntries()/file.Get("Events").Get("WH_htt125").GetBinContent(1)*10
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ZH_htt125").GetEntries()/file.Get("Events").Get("ZH_htt125").GetBinContent(1)*10
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ttH_htt125").GetEntries()/file.Get("Events").Get("ttH_htt125").GetBinContent(1)*10

         xs[12]=xs[12]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)*file.Get(dir_nnlops).Get("ggH_htt125").GetEntries()/file.Get("Events").Get("ggH_htt125").GetBinContent(1)*10
         xs[12]=xs[12]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("qqH_htt125").GetEntries()/file.Get("Events").Get("qqH_htt125").GetBinContent(1)*10
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ggZH_lep_htt125_scale").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_lep_htt125").GetEntries()/file.Get("Events").Get("ggZH_lep_htt125").GetBinContent(1)*10
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ggZH_had_htt125_scale").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_had_htt125").GetEntries()/file.Get("Events").Get("ggZH_had_htt125").GetBinContent(1)*10
         xs[12]=xs[12]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("WH_htt125").GetEntries()/file.Get("Events").Get("WH_htt125").GetBinContent(1)*10
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ZH_htt125_scale").GetBinContent(j)*file.Get(dir_powheg).Get("ZH_htt125").GetEntries()/file.Get("Events").Get("ZH_htt125").GetBinContent(1)*10
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ttH_htt125").GetEntries()/file.Get("Events").Get("ttH_htt125").GetBinContent(1)*10

         xs[13]=xs[13]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)*file.Get(dir_nnlops).Get("ggH_htt125").GetEntries()/file.Get("Events").Get("ggH_htt125").GetBinContent(1)*10
         xs[13]=xs[13]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("qqH_htt125").GetEntries()/file.Get("Events").Get("qqH_htt125").GetBinContent(1)*10
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_lep_htt125").GetEntries()/file.Get("Events").Get("ggZH_lep_htt125").GetBinContent(1)*10
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ggZH_had_htt125").GetEntries()/file.Get("Events").Get("ggZH_had_htt125").GetBinContent(1)*10
         xs[13]=xs[13]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("WH_htt125").GetEntries()/file.Get("Events").Get("WH_htt125").GetBinContent(1)*10
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)*file.Get(dir_powheg).Get("ZH_htt125").GetEntries()/file.Get("Events").Get("ZH_htt125").GetBinContent(1)*10
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ttH_htt125_scale").GetBinContent(j)*file.Get(dir_powheg).Get("ttH_htt125").GetEntries()/file.Get("Events").Get("ttH_htt125").GetBinContent(1)*10



         xs_perbin.append(1000*xs[0])
         print xs_perbin


       xs_scale_2=0.0
       for gg in range(0,13):
#         print "gg is ", gg, "  xs_scale_2 is ", xs_scale_2, "  xs[gg]=", xs[gg]
         xs_scale_2=xs_scale_2+(xs[0]-xs[gg+1])*(xs[0]-xs[gg+1])
       xs_scale_2=xs_scale_2+(0.0206*0.0206*xs[0]*xs[0]) # BR tau
       xs_scale_2=xs_scale_2+(0.03*0.03*xs[0]*xs[0]) # PDF
       print "Total xs ", 1000*xs[0],1000*(xs_scale_2**0.5)


       for i in range(1,5):
         print xs_perbin[i]-xs_perbin[i-1]



if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--TheoryInput', '-i', required=True, help='Theory Input file where the fiducial custa re defined')
    parser.add_argument('--Var', '-v', required=True, help='Higgs Combine outcome of jet pT')
    
    main(parser.parse_args())



# Using Pt Higgs
# --- MultiDimFit ---
#best fit parameter values and profile-likelihood uncertainties:
#        mu_fid :    +2.663   -0.672/+0.875 (68%)
#     rho_0_350 :    +1.195   -0.476/+0.494 (68%)
#   rho_350_450 :    +0.662   -0.364/+0.367 (68%)
#   rho_450_600 :    +1.682   -0.390/+0.410 (68%)



# Using Pt Higgs previously
# --- MultiDimFit ---
#best fit parameter values and profile-likelihood uncertainties:
#        mu_fid :    +2.633   -0.668/+0.883 (68%)
#     rho_0_350 :    +1.245   -0.466/+0.446 (68%)
# Warning - No valid low-error found, will report difference to minimum of range for : rho_350_450
#   rho_350_450 :    +0.678   -15.678/+0.360 (68%)
#   rho_450_600 :    +1.639   -0.428/+0.497 (68%)
#Done in 6.57 min (cpu), 6.58 min (real)
