from glob import glob
from ROOT import *
import sys



#OutFile=TFile('out'+weightt_name+'.root',"RECREATE")
#OutFile.cd()
Before=TH1F('Before','Before',50,0,1)
After_MVA=TH1F('After_MVA','After_MVA',50,0,1)
After_Cmb=TH1F('After_Cmb','After_Cmb',50,0,1)
After_Chr=TH1F('After_Chr','After_Chr',50,0,1)
#
#OutHist_BSM=TH1F(weightt_name+'_bsm',weightt_name+'_bsm',10,0,1)
#tDirectory= OutFile.mkdir("inc")
##    tDirectory_ex= OutFile.mkdir("excl")
#tDirectory.cd()



file=TFile(sys.argv[1],'read')

c=TCanvas()
gStyle.SetOptStat(0)

tr_BSM=file.Get('tautau_tree')
for evt_BSM in tr_BSM:
    
    Before.Fill(tr_BSM.dR_tau_tau)
    if tr_BSM.PassLead and tr_BSM.PassSub: After_MVA.Fill(tr_BSM.dR_tau_tau)
    if tr_BSM.PassLeadCombined and tr_BSM.PassSubCombined: After_Cmb.Fill(tr_BSM.dR_tau_tau)
    if tr_BSM.PassLeadCharged and tr_BSM.PassSubCharged: After_Chr.Fill(tr_BSM.dR_tau_tau)

Before.SetLineColor(4)
After_MVA.SetLineColor(2)
After_Cmb.SetLineColor(2)
After_Chr.SetLineColor(2)

Before.GetXaxis().SetTitle('dR_tau_tau')
Before.SetTitle('')

Before.Draw()
After_MVA.Draw('same')
leg=TLegend(0.1,.7,0.45,.9)
leg.AddEntry(Before,'No Isolation','lp')
leg.AddEntry(After_MVA,'Both Tau Pass L MVA Iso','lp')
leg.Draw()
c.SaveAs('_check_mva.pdf')



Before.Draw()
After_Cmb.Draw('same')
leg1=TLegend(0.1,.7,0.45,.9)
leg1.AddEntry(Before,'No Isolation','lp')
leg1.AddEntry(After_Cmb,'Both Tau Pass L Combined Iso','lp')
leg1.Draw()
c.SaveAs('_check_cmb.pdf')

Before.Draw()
After_Chr.Draw('same')
leg2=TLegend(0.1,.7,0.45,.9)
leg2.AddEntry(Before,'No Isolation','lp')
leg2.AddEntry(After_Chr,'Both Tau Pass L Charged Iso','lp')
leg2.Draw()
c.SaveAs('_check_chr.pdf')


#
#    if tr_BSM.cat_vbf < 1: continue
#    if tr_BSM.OS < 1: continue
#    if tr_BSM.is_signal < 1: continue
#    if tr_BSM.ME_sm_VBF == 0: continue
#
#
#
#
##fileList= [ifile for ifile in glob("./wt*.root") if "rew" in ifile]
##fileList= [ifile for ifile in glob("./wt*.root")]
#
#W_a2=0.05 *4
#W_a3=0.04 *8.5
#W_l1=1540000 *4.5
#W_l1zg=7840000 *4
#
#fileList=[
#  ['vbf_a2_VBF125_output.root','ME_a2_VBF','Da2'],
##  ['vbf_a2int/vbf_a2int.root
#  ['vbf_a3_VBF125_output.root','ME_ps_vbf','Da3'],
##  ['vbf_a3int/vbf_a3int.root
#  ['vbf_l1_VBF125_output.root','ME_L1_VBF','DL1'],
#  ['vbf_l1Zg_VBF125_output.root','ME_L1Zg_VBF','DL1Zg'],
##  ['vbf_l1Zgint/vbf_l1Zgint.root
##  ['vbf_l1int/vbf_l1int.root
#]
#
##['vbf_a1/vbf_a1.root]
#
#
#
#location='Output/trees/New2018_No_Change/_nominal/'
#for file in fileList:
#
#    c=TCanvas()
#    gStyle.SetOptStat(0)
#    print file[0]
#
#    weightt_name=file[1]
#    print weightt_name
#
#
#
#    inclusive=TFile(location+file[0],'read')
#    print 'name= ', inclusive.GetName()
#    tr_BSM=inclusive.Get('tautau_tree')
#    for evt_BSM in tr_BSM:
#
#        if tr_BSM.cat_vbf < 1: continue
#        if tr_BSM.OS < 1: continue
#        if tr_BSM.is_signal < 1: continue
#        if tr_BSM.ME_sm_VBF == 0: continue
#
##        print "\t BSM", tr_BSM.ME_sm_VBF, tr_BSM.ME_sm_VBF, tr_BSM.ME_ps_vbf, tr_BSM.ME_a2_VBF, tr_BSM.ME_L1_VBF,tr_BSM.ME_L1Zg_VBF
#
#        if file[1]=='ME_ps_vbf':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_a3*tr_BSM.ME_ps_vbf),tr_BSM.evtwt) ; W_=W_a3
#        elif file[1]=='ME_a2_VBF':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_a2*tr_BSM.ME_a2_VBF),tr_BSM.evtwt) ; W_=W_a2
#        elif file[1]=='ME_L1_VBF':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_l1*tr_BSM.ME_L1_VBF),tr_BSM.evtwt) ; W_=W_l1
#        elif file[1]=='ME_L1Zg_VBF':
#            OutHist_BSM.Fill(tr_BSM.ME_sm_VBF/(tr_BSM.ME_sm_VBF+W_l1zg*tr_BSM.ME_L1Zg_VBF),tr_BSM.evtwt) ; W_=W_l1zg
#        else:
#            print "WOOOW"
#
#
#    SM_file=TFile(location+'vbf_a1_VBF125_output.root','read')
#    print 'name SM_file = ', SM_file.GetName()
#    tr_sm=SM_file.Get('emu_tree')
#    for evt_sm in tr_sm:
#
#        if tr_sm.cat_vbf < 1: continue
#        if tr_sm.OS < 1: continue
#        if tr_sm.is_signal < 1: continue
#        if tr_sm.ME_sm_VBF == 0: continue
#
##        print "\t SM",  tr_sm.ME_sm_VBF, tr_sm.ME_sm_VBF, tr_sm.ME_ps_vbf, tr_sm.ME_a2_VBF
#        if file[1]=='ME_ps_vbf':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_a3*tr_sm.ME_ps_vbf),tr_sm.evtwt)
#        if file[1]=='ME_a2_VBF':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_a2*tr_sm.ME_a2_VBF),tr_sm.evtwt)
#        if file[1]=='ME_L1_VBF':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_l1*tr_sm.ME_L1_VBF),tr_sm.evtwt)
#        if file[1]=='ME_L1Zg_VBF':
#            OutHist_sm.Fill(tr_sm.ME_sm_VBF/(tr_sm.ME_sm_VBF+W_l1zg*tr_sm.ME_L1Zg_VBF),tr_sm.evtwt)
#
#
#    OutHist_BSM.SetMarkerSize(0.7)
#    OutHist_BSM.SetMarkerColor(4)
#    OutHist_BSM.SetMarkerStyle(20)
#    OutHist_BSM.GetXaxis().SetTitle(weightt_name.replace('ME_','D '))
#
##    print "now weightt_name",OutHist_BSM.Integral()
#    OutHist_BSM.Scale(1./OutHist_BSM.Integral())
#    tDirectory.WriteObject(OutHist_BSM,weightt_name)
#    axis = OutHist_BSM.GetXaxis();
#    Yaxis = OutHist_BSM.GetYaxis();
#    Yaxis.SetRangeUser(0,0.7)
#    bmin = axis.FindBin(0);
#    bmax = axis.FindBin(0.5);
#    bmax2 = axis.FindBin(1);
#    print 'BSM integral 0.0.5', OutHist_BSM.Integral(bmin,bmax)
##    print 'BSM integral 0.1', OutHist_BSM.Integral(bmin,bmax2)
#    OutHist_BSM.DrawNormalized('e')
#
#
#    OutHist_sm.SetMarkerSize(0.7)
#    OutHist_sm.SetMarkerColor(2)
#    OutHist_sm.SetMarkerStyle(24)
#    OutHist_sm.DrawNormalized('esame')
#    OutHist_sm.Scale(1./OutHist_sm.Integral())
#    tDirectory.WriteObject(OutHist_sm,weightt_name)
#    axis = OutHist_sm.GetXaxis();
#    bmin = axis.FindBin(0);
#    bmax = axis.FindBin(0.5);
#    bmax2 = axis.FindBin(1);
#    print '\t SM integral 0.0.5', OutHist_sm.Integral(bmax,bmax2)
##    print '\t SM integral 0.1', OutHist_sm.Integral(bmin,bmax2)
#
#
#    leg=TLegend(0.1,.7,0.45,.9)
#    leg.AddEntry(OutHist_BSM,weightt_name.replace('ME_','BSM_'),'lp')
#    leg.AddEntry(OutHist_sm,weightt_name.replace('ME_','SM_'),'lp')
#    leg.Draw()
#
#    text=TText(0.2,0.3,'BSM[0,0.5]=%.3f '%OutHist_BSM.Integral(bmin,bmax))
#    text.SetTextFont (   41 )
#    text.Draw()
#    text2=TText(0.2,0.35,'SM[0.5,1]=%.3f '%OutHist_sm.Integral(bmax,bmax2))
#    text2.SetTextFont (   41 )
#    text2.Draw()
#    text4=TText(0.2,0.4,'w=%.3f'%W_)
#    text4.SetTextFont (   41 )
#    text4.Draw()
#    text3=TText(0.2,0.45,'D=ME_{sm}/(ME_{sm}+ w * ME_{bsm})')
#    text3.SetTextFont (   41 )
#    text3.Draw()
#
#
#    c.SaveAs(weightt_name+'.pdf')
##    c.SaveAs(file.replace("./","_ROOT"))
##    OutHist_BSM
##    OutHist_sm.Write()
##    OutHist_BSM.Write()
#    OutFile.Close()
