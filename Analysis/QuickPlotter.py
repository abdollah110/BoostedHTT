from glob import glob
from ROOT import *
import sys

inputFile=sys.argv[1]

c=TCanvas()
gStyle.SetOptStat(0)
print file[0]
    
weightt_name=file[1]
print weightt_name

InFile=TFile(inputFile,'r')
OutFile=TFile('out'+inputFile,"RECREATE")
OutFile.cd()
OutHist_sm=TH1F(weightt_name,weightt_name,10,0,1)

tr_BSM=InFile.Get('tautau_tree')
for evt_BSM in tr_BSM:
    
#    if tr_BSM.cat_vbf < 1: continue
#    if tr_BSM.OS < 1: continue
#    if tr_BSM.is_signal < 1: continue
#    if tr_BSM.ME_sm_VBF == 0: continue
    OutHist_BSM.Fill()

#        print "\t BSM", tr_BSM.ME_sm_VBF, tr_BSM.ME_sm_VBF, tr_BSM.ME_ps_vbf, tr_BSM.ME_a2_VBF, tr_BSM.ME_L1_VBF,tr_BSM.ME_L1Zg_VBF
#VBF_MELA =  (evt->ME_sm_ggH() + evt->ME_ps_ggH()) / (evt->ME_sm_ggH() + evt->ME_ps_ggH() + 8 * evt->ME_sm_VBF());



        if file[1]=='ME_ps_ggH':
            OutHist_BSM.Fill( (tr_BSM.ME_sm_ggH + tr_BSM.ME_ps_ggH) /(tr_BSM.ME_sm_ggH + tr_BSM.ME_ps_ggH +W_a3*tr_BSM.ME_sm_VBF),tr_BSM.evtwt) ; W_=W_a3
#        elif file[1]=='ME_a2_VBF':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_a2*tr_BSM.ME_a2_VBF),tr_BSM.evtwt) ; W_=W_a2
#        elif file[1]=='ME_L1_VBF':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_l1*tr_BSM.ME_L1_VBF),tr_BSM.evtwt) ; W_=W_l1
#        elif file[1]=='ME_L1Zg_VBF':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_l1zg*tr_BSM.ME_L1Zg_VBF),tr_BSM.evtwt) ; W_=W_l1zg
        else:
            print "WOOOW"


#    SM_file=TFile(location+'ggH_madgraph_twojet_ps_ggH125_output.root','read')
    SM_file=TFile(location+'ggH_madgraph_twojet_nominal_ggH125_output.root','read')
    print 'name SM_file = ', SM_file.GetName()
    tr_sm=SM_file.Get('emu_tree')
    for evt_sm in tr_sm:

        if tr_sm.cat_vbf < 1: continue
        if tr_sm.OS < 1: continue
        if tr_sm.is_signal < 1: continue
#        if tr_sm.ME_sm_ggH == 0: continue
        
#        print "\t SM",  tr_sm.ME_sm_VBF, tr_sm.ME_sm_VBF, tr_sm.ME_ps_vbf, tr_sm.ME_a2_VBF
        if file[1]=='ME_ps_ggH':
            OutHist_sm.Fill( (tr_sm.ME_sm_ggH + tr_sm.ME_sm_ggH) /(tr_sm.ME_sm_ggH + tr_sm.ME_sm_ggH +W_a3*tr_sm.ME_sm_VBF),tr_sm.evtwt)
#        if file[1]=='ME_a2_VBF':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_a2*tr_sm.ME_a2_VBF),tr_sm.evtwt)
#        if file[1]=='ME_L1_VBF':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_l1*tr_sm.ME_L1_VBF),tr_sm.evtwt)
#        if file[1]=='ME_L1Zg_VBF':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_l1zg*tr_sm.ME_L1Zg_VBF),tr_sm.evtwt)


    OutHist_BSM.SetMarkerSize(0.7)
    OutHist_BSM.SetMarkerColor(4)
    OutHist_BSM.SetMarkerStyle(20)
    OutHist_BSM.GetXaxis().SetTitle(weightt_name.replace('ME_','D '))
    
#    print "now weightt_name",OutHist_BSM.Integral()
    OutHist_BSM.Scale(1./OutHist_BSM.Integral())
    tDirectory.WriteObject(OutHist_BSM,weightt_name)
    axis = OutHist_BSM.GetXaxis();
    Yaxis = OutHist_BSM.GetYaxis();
    Yaxis.SetRangeUser(0,0.7)
    bmin = axis.FindBin(0);
    bmax = axis.FindBin(0.5);
    bmax2 = axis.FindBin(1);
    print 'BSM integral 0.0.5', OutHist_BSM.Integral(bmin,bmax)
#    print 'BSM integral 0.1', OutHist_BSM.Integral(bmin,bmax2)
    OutHist_BSM.DrawNormalized('e')
    
    
    OutHist_sm.SetMarkerSize(0.7)
    OutHist_sm.SetMarkerColor(2)
    OutHist_sm.SetMarkerStyle(24)
    OutHist_sm.DrawNormalized('esame')
    OutHist_sm.Scale(1./OutHist_sm.Integral())
    tDirectory.WriteObject(OutHist_sm,weightt_name)
    axis = OutHist_sm.GetXaxis();
    bmin = axis.FindBin(0);
    bmax = axis.FindBin(0.5);
    bmax2 = axis.FindBin(1);
    print '\t SM integral 0.0.5', OutHist_sm.Integral(bmax,bmax2)
#    print '\t SM integral 0.1', OutHist_sm.Integral(bmin,bmax2)
    

    leg=TLegend(.4,.8,.6,.9)
    leg.AddEntry(OutHist_BSM,weightt_name.replace('ME_','VBF '),'lp')
    leg.AddEntry(OutHist_sm,weightt_name.replace('ME_','ggH '),'lp')
    leg.Draw()

    text=TText(0.2,0.3,'VBF[0,0.5]=%.3f '%OutHist_BSM.Integral(bmin,bmax))
    text.SetTextFont (   41 )
    text.Draw()
    text2=TText(0.2,0.35,'ggH[0.5,1]=%.3f '%OutHist_sm.Integral(bmax,bmax2))
    text2.SetTextFont (   41 )
    text2.Draw()
    text4=TText(0.2,0.4,'w=%.3f'%W_)
    text4.SetTextFont (   41 )
    text4.Draw()
    text3=TText(0.2,0.45,'D=ME_{ggh_sm}+ME_{ggh_bsm}/(ME_{ggh_sm}+ME_{ggh_bsm}+ w * ME_{vbf_sm})')
    text3.SetTextFont (   41 )
    text3.Draw()


    c.SaveAs(weightt_name+'_vbfMELA.pdf')
#    c.SaveAs(file.replace("./","_ROOT"))
#    OutHist_BSM
#    OutHist_sm.Write()
#    OutHist_BSM.Write()
    OutFile.Close()

#
#
#hadd All_emu_2016_preNN/NN_nominal/_qqH_inc.root All_emu_2016_preNN/NN_nominal/reweighted_qqH_htt_0*root
#hadd All_emu_2016_preNN/NN_nominal/_WH_inc.root All_emu_2016_preNN/NN_nominal/reweighted_WH_htt_0*root
#hadd All_emu_2016_preNN/NN_nominal/_ZH_inc.root All_emu_2016_preNN/NN_nominal/reweighted_ZH_htt_0*root
#mv All_emu_2016_preNN/NN_nominal/reweighted*root All_emu_2016_preNN/NN_nominal/Other/.
#
#hadd All_emu_2017_preNN/NN_nominal/_qqH_inc.root All_emu_2017_preNN/NN_nominal/reweighted_qqH_htt_0*root
#hadd All_emu_2017_preNN/NN_nominal/_WH_inc.root All_emu_2017_preNN/NN_nominal/reweighted_WH_htt_0*root
#hadd All_emu_2017_preNN/NN_nominal/_ZH_inc.root All_emu_2017_preNN/NN_nominal/reweighted_ZH_htt_0*root
#mv All_emu_2017_preNN/NN_nominal/reweighted*root All_emu_2017_preNN/NN_nominal/Other/.
#
#hadd All_emu_2018_preNN/NN_nominal/_qqH_inc.root All_emu_2018_preNN/NN_nominal/reweighted_qqH_htt_0*root
#hadd All_emu_2018_preNN/NN_nominal/_WH_inc.root All_emu_2018_preNN/NN_nominal/reweighted_WH_htt_0*root
#hadd All_emu_2018_preNN/NN_nominal/_ZH_inc.root All_emu_2018_preNN/NN_nominal/reweighted_ZH_htt_0*root
#mv All_emu_2018_preNN/NN_nominal/reweighted*root All_emu_2018_preNN/NN_nominal/Other/.
