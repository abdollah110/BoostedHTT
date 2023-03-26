#!/usr/bin/env python
import ROOT
import re
import array

def add_lumiall():
    lowX=0.65
    lowY=0.835
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.30, lowY+0.16, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    lumi.AddText("138 fb^{-1} (13 TeV)")
    return lumi


def add_CMS():
    lowX=0.2
    lowY=0.72
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS Preliminary")
    return lumi

def add_Preliminary():
    lowX=0.2
    lowY=0.64
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.055)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    #lumi.AddText("Preliminary")
    return lumi

def make_legend():
        output = ROOT.TLegend(0.35, 0.52, 0.96, 0.76, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
 	output.SetNColumns(1)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetOptStat(0)
#ROOT.gStyle.SetErrorX(0)


def main(args):

    c=ROOT.TCanvas("canvas","",0,0,600,600)
    c.cd()

#    file=ROOT.TFile("differential_theory_3.root","r")
    file=ROOT.TFile(args.TheoryInput,"r")

    adapt=ROOT.gROOT.GetColor(12)
    new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
    trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

    nvar=2
#    nvar=1
    variable=["hpt","jpt"]
    xaxis=["p_{T}^{H} (GeV)","p_{T}^{j_{1}} (GeV)"]
    yaxis=["d#sigma_{fid}/dp_{T}(H) (fb/GeV)","d#sigma_{fid}/dp_{T}(jet) (fb/GeV)"]
    postfix=["_THU_ggH_Mu","_THU_ggH_Res","_THU_ggH_Mig01","_THU_ggH_Mig12","_THU_ggH_VBF2j","_THU_ggH_VBF3j","_THU_ggH_PT60","_THU_ggH_PT120","_THU_ggH_qmtop"]

#       dir_nnlops=variable[k]+"_nnlops_tautrg"
#       dir_powheg=variable[k]+"_powheg_tautrg"



    for kkkk in range(0,nvar):

       dir_nnlops=variable[kkkk]+"_nnlops_tautrg"
       dir_powheg=variable[kkkk]+"_powheg_tautrg"

       if 'hpt' in args.JetPtLimit: k =0 ; VarName='PTH'
       elif 'jpt' in args.JetPtLimit: k =1 ; VarName='PTJ'
       else: print 'which var are you plotting for '
    
       xs=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
       print 'file.Get(dir_nnlops).Get("ggH_htt125").GetSize() is ', file.Get(dir_nnlops).Get("ggH_htt125").GetSize()
       for j in range(1,file.Get(dir_nnlops).Get("ggH_htt125").GetSize()-1):
         xs[0]=xs[0]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)
         print 'bin ', j, '   val is', xs[0]
         xs[0]=xs[0]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)
         xs[0]=xs[0]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)
         xs[0]=xs[0]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)
         for z in range(0,9):
            xs[z+1]=xs[z+1]+file.Get(dir_nnlops).Get("ggH_htt125"+postfix[z]).GetBinContent(j)
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)
            xs[z+1]=xs[z+1]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)

         xs[10]=xs[10]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)
         xs[10]=xs[10]+file.Get(dir_powheg).Get("qqH_htt125_scale").GetBinContent(j)
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)
         xs[10]=xs[10]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)
         xs[10]=xs[10]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)

         xs[11]=xs[11]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)
         xs[11]=xs[11]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)
         xs[11]=xs[11]+file.Get(dir_powheg).Get("WH_htt125_scale").GetBinContent(j)
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)
         xs[11]=xs[11]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)

         xs[12]=xs[12]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)
         xs[12]=xs[12]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ggZH_lep_htt125_scale").GetBinContent(j)
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ggZH_had_htt125_scale").GetBinContent(j)
         xs[12]=xs[12]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ZH_htt125_scale").GetBinContent(j)
         xs[12]=xs[12]+file.Get(dir_powheg).Get("ttH_htt125").GetBinContent(j)

         xs[13]=xs[13]+file.Get(dir_nnlops).Get("ggH_htt125").GetBinContent(j)
         xs[13]=xs[13]+file.Get(dir_powheg).Get("qqH_htt125").GetBinContent(j)
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ggZH_lep_htt125").GetBinContent(j)
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ggZH_had_htt125").GetBinContent(j)
         xs[13]=xs[13]+file.Get(dir_powheg).Get("WH_htt125").GetBinContent(j)
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ZH_htt125").GetBinContent(j)
         xs[13]=xs[13]+file.Get(dir_powheg).Get("ttH_htt125_scale").GetBinContent(j)

       xs_scale_2=0.0
       for gg in range(0,13):
         xs_scale_2=xs_scale_2+(xs[0]-xs[gg+1])*(xs[0]-xs[gg+1])
       xs_scale_2=xs_scale_2+(0.0206*0.0206*xs[0]*xs[0]) # BR tau  // why BR is not multiplied to xs_scale_2
       xs_scale_2=xs_scale_2+(0.03*0.03*xs[0]*xs[0]) # PDF
       print "xs ",1000*xs[0],1000*(xs_scale_2**0.5)


       ggH_powheg=file.Get(dir_powheg).Get("ggH_htt125")
       for j in range(1,ggH_powheg.GetSize()-1):
         ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.0206*0.0206*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #BR tau
         ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.032*0.032*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #PDF gg
         ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.05*0.05*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #Pythia scale
         for z in range(0,9):
             ggH_powheg_alternative=file.Get(dir_powheg).Get("ggH_htt125"+postfix[z])
             unc=abs(ggH_powheg_alternative.GetBinContent(j)-ggH_powheg.GetBinContent(j))
             ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+unc*unc)**0.5)

       ggH_nnlops=file.Get(dir_nnlops).Get("ggH_htt125")
       for j in range(1,ggH_powheg.GetSize()-1):
         ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.0206*0.0206*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) # BR tau
         ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.032*0.032*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) # PDF gg
         ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.05*0.05*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) #Pythia scale
         for z in range(0,9):
             ggH_nnlops_alternative=file.Get(dir_nnlops).Get("ggH_htt125"+postfix[z])
             unc=abs(ggH_nnlops_alternative.GetBinContent(j)-ggH_nnlops.GetBinContent(j))
             ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+unc*unc)**0.5)
        
       for j in range(1,ggH_powheg.GetSize()-1):
         print ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinWidth(j),ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinWidth(j)

       qqH=file.Get(dir_powheg).Get("qqH_htt125")
       WH=file.Get(dir_powheg).Get("WH_htt125")
       ZH=file.Get(dir_powheg).Get("ZH_htt125")
       ggZH_lep=file.Get(dir_powheg).Get("ggZH_lep_htt125")
       ggZH_had=file.Get(dir_powheg).Get("ggZH_had_htt125")
       ttH=file.Get(dir_powheg).Get("ttH_htt125")


       for j in range(1,ggH_powheg.GetSize()-1):
          #BR tau
          qqH.SetBinError(j,(qqH.GetBinError(j)*qqH.GetBinError(j)+0.0206*0.0206*qqH.GetBinContent(j)*qqH.GetBinContent(j))**0.5)
          WH.SetBinError(j,(WH.GetBinError(j)*WH.GetBinError(j)+0.0206*0.0206*WH.GetBinContent(j)*WH.GetBinContent(j))**0.5)
          ZH.SetBinError(j,(ZH.GetBinError(j)*ZH.GetBinError(j)+0.0206*0.0206*ZH.GetBinContent(j)*ZH.GetBinContent(j))**0.5)
          ttH.SetBinError(j,(ttH.GetBinError(j)*ttH.GetBinError(j)+0.0206*0.0206*ttH.GetBinContent(j)*ttH.GetBinContent(j))**0.5)
          ggZH_had.SetBinError(j,(ggZH_had.GetBinError(j)*ggZH_had.GetBinError(j)+0.0206*0.0206*ggZH_had.GetBinContent(j)*ggZH_had.GetBinContent(j))**0.5)
          ggZH_lep.SetBinError(j,(ggZH_lep.GetBinError(j)*ggZH_lep.GetBinError(j)+0.0206*0.0206*ggZH_lep.GetBinContent(j)*ggZH_lep.GetBinContent(j))**0.5)

          #PDF
          qqH.SetBinError(j,(qqH.GetBinError(j)*qqH.GetBinError(j)+0.021*0.021*qqH.GetBinContent(j)*qqH.GetBinContent(j))**0.5)
          WH.SetBinError(j,(WH.GetBinError(j)*WH.GetBinError(j)+0.018*0.018*WH.GetBinContent(j)*WH.GetBinContent(j))**0.5)
          ZH.SetBinError(j,(ZH.GetBinError(j)*ZH.GetBinError(j)+0.013*0.013*ZH.GetBinContent(j)*ZH.GetBinContent(j))**0.5)

#             note, there is no qcd scale for qqH FIXME
          qqH_alternative=file.Get(dir_powheg).Get("qqH_htt125_scale")
          unc=abs(qqH_alternative.GetBinContent(j)-qqH.GetBinContent(j))
          qqH.SetBinError(j,(qqH.GetBinError(j)*qqH.GetBinError(j)+unc*unc)**0.5)

          WH_alternative=file.Get(dir_powheg).Get("WH_htt125_scale")
          unc=abs(WH_alternative.GetBinContent(j)-WH.GetBinContent(j))
          WH.SetBinError(j,(WH.GetBinError(j)*WH.GetBinError(j)+unc*unc)**0.5)

          ZH_alternative=file.Get(dir_powheg).Get("ZH_htt125_scale")
          unc=abs(ZH_alternative.GetBinContent(j)-ZH.GetBinContent(j))
          ZH.SetBinError(j,(ZH.GetBinError(j)*ZH.GetBinError(j)+unc*unc)**0.5)

          ggZH_lep_alternative=file.Get(dir_powheg).Get("ggZH_lep_htt125_scale")
          unc=abs(ggZH_lep_alternative.GetBinContent(j)-ggZH_lep.GetBinContent(j))
          ggZH_lep.SetBinError(j,(ggZH_lep.GetBinError(j)*ggZH_lep.GetBinError(j)+unc*unc)**0.5)

          ggZH_had_alternative=file.Get(dir_powheg).Get("ggZH_had_htt125_scale")
          unc=abs(ggZH_had_alternative.GetBinContent(j)-ggZH_had.GetBinContent(j))
          ggZH_had.SetBinError(j,(ggZH_had.GetBinError(j)*ggZH_had.GetBinError(j)+unc*unc)**0.5)

          ttH_alternative=file.Get(dir_powheg).Get("ttH_htt125_scale")
          unc=abs(ttH_alternative.GetBinContent(j)-ttH.GetBinContent(j))
          ttH.SetBinError(j,(ttH.GetBinError(j)*ttH.GetBinError(j)+unc*unc)**0.5)

       XH=WH.Clone()
       
       XH.Add(ZH)
       XH.Add(qqH)
       XH.Add(ggZH_lep)
       XH.Add(ggZH_had)
       XH.Add(ttH)

       ggH_powheg.Add(XH)
       ggH_nnlops.Add(XH)

       ggH_powheg_RB=ggH_powheg.Clone()
       ggH_nnlops_RB=ggH_nnlops.Clone()
       XH_RB=XH.Clone()
    

       if 'hpt' in args.JetPtLimit:
        
           xbins = array.array('d', [250,350,450,600,2000])
           ggH_powheg_RB=ggH_powheg.Rebin(4,'numHistRB',xbins)
           ggH_nnlops_RB=ggH_nnlops.Rebin(4,'numHistRB_b',xbins)
           XH_RB=XH.Rebin(4,'numHistRB_bXH',xbins)
       
       for j in range(0,ggH_powheg.GetSize()-2):
         width=ggH_powheg_RB.GetBinWidth(j+1)
         ggH_powheg_RB.SetBinContent(j+1,ggH_powheg.GetBinContent(j+1)/width)
         ggH_nnlops_RB.SetBinContent(j+1,ggH_nnlops.GetBinContent(j+1)/width)
         XH.SetBinContent(j+1,XH.GetBinContent(j+1)/width)
         ggH_powheg_RB.SetBinError(j+1,ggH_powheg.GetBinError(j+1)/width)
         ggH_nnlops_RB.SetBinError(j+1,ggH_nnlops.GetBinError(j+1)/width)
         XH_RB.SetBinError(j+1,XH.GetBinError(j+1)/width)
       
       ggH_powheg_RB.GetXaxis().SetTitle("")
       ggH_powheg_RB.GetXaxis().SetTitleSize(0)
       ggH_powheg_RB.GetXaxis().SetNdivisions(505)
       ggH_powheg_RB.GetYaxis().SetLabelFont(42)
       ggH_powheg_RB.GetYaxis().SetLabelOffset(0.01)
       ggH_powheg_RB.GetYaxis().SetLabelSize(0.06)
       ggH_powheg_RB.GetYaxis().SetTitleSize(0.075)
       ggH_powheg_RB.GetYaxis().SetTitleOffset(1.04)
       ggH_powheg_RB.SetTitle("")
       ggH_powheg_RB.GetYaxis().SetTitle(yaxis[k])
       #ggH_powheg_RB.SetMinimum(0.1)
       if k<4: ggH_powheg_RB.SetMinimum(ggH_powheg_RB.GetBinContent(ggH_powheg_RB.GetSize()-2)/10)
       if k<4: ggH_powheg_RB.SetMaximum(7*ggH_powheg_RB.GetMaximum())
       if k==4: ggH_powheg_RB.SetMinimum(0)
       if k==4: ggH_powheg_RB.SetMaximum(2*ggH_powheg_RB.GetMaximum())
#       if k<2: ggH_powheg_RB.SetMaximum(200*ggH_powheg_RB.GetMaximum())
       if k<2: ggH_powheg_RB.SetMaximum(10)
       if k==0: ggH_powheg_RB.GetXaxis().SetLimits(250,2000)
       if k==0: ggH_powheg_RB.SetMinimum(.0000001)
       if k==1: ggH_powheg_RB.SetMinimum(.0000001)
       ggH_powheg_RB.SetMarkerStyle(20)
       ggH_powheg_RB.SetMarkerSize(1)
       ggH_powheg_RB.GetXaxis().SetLabelSize(0)
       
       pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
       pad1.Draw()
       pad1.cd()
       pad1.SetFillColor(0)
       pad1.SetBorderMode(0)
       pad1.SetBorderSize(10)
       pad1.SetTickx(1)
       pad1.SetTicky(1)
       pad1.SetLeftMargin(0.18)
       pad1.SetRightMargin(0.05)
       pad1.SetTopMargin(0.122)
       pad1.SetBottomMargin(0.026)
       pad1.SetFrameFillStyle(0)
       pad1.SetFrameLineStyle(0)
       pad1.SetFrameBorderMode(0)
       pad1.SetFrameBorderSize(10)
       if k<4: pad1.SetLogy()

       #ggH_powheg_RB.SetLineColor(2)
       #ggH_nnlops.SetLineColor(3)
       #XH.SetFillColor(4)

       ggH_powheg_RB.SetLineColor(ROOT.TColor.GetColor("#9999cc"))
       ggH_nnlops_RB.SetLineColor(ROOT.TColor.GetColor("#12cadd"))
       XH.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))
       XH.SetLineColor(ROOT.TColor.GetColor("#ffcc66"))
       ggH_powheg_RB.SetLineWidth(3)
       ggH_nnlops_RB.SetLineWidth(3)

       xList = [1,2,3,4,0,0,0,0,0]
       yList = [1,4,9,16,0,0,0,0,0]
       xhighList = [0,0,0,0,0,0,0,0,0]
       yhighList = [1+1,4+1,9+1,16+1,0,0,0,0,0]
       xlowList = [0,0,0,0,0,0,0,0,0]
       ylowList = [1-1,4-1,9-1,16-1,0,0,0,0,0]

       ListOfLimit_0_350=[]
       ListOfLimit_350_450=[]
       ListOfLimit_450_600=[]
       ListOfLimit_GT600=[]


#       with open('{}/higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_0_350.root_scan.txt'.format(args.InputDir),'r') as f:
       with open('{}/scan_r_H_{}_0_350.txt'.format(args.InputDir,VarName),'r') as f:
            lines=f.readline()
            ListOfLimit_0_350.append(float(lines.split(" ")[2]))
            ListOfLimit_0_350.append(abs(float(lines.split(" ")[3])))
            ListOfLimit_0_350.append(abs(float(lines.split(" ")[4])))


#       with open('{}/higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_350_450.root_scan.txt'.format(args.InputDir),'r') as f:
       with open('{}/scan_r_H_{}_350_450.txt'.format(args.InputDir,VarName),'r') as f:
            lines=f.readline()
            ListOfLimit_350_450.append(float(lines.split(" ")[2]))
            ListOfLimit_350_450.append(abs(float(lines.split(" ")[3])))
            ListOfLimit_350_450.append(abs(float(lines.split(" ")[4])))

#       with open('{}/higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_450_600.root_scan.txt'.format(args.InputDir),'r') as f:
       with open('{}/scan_r_H_{}_450_600.txt'.format(args.InputDir,VarName),'r') as f:
            lines=f.readline()
            ListOfLimit_450_600.append(float(lines.split(" ")[2]))
            ListOfLimit_450_600.append(abs(float(lines.split(" ")[3])))
            ListOfLimit_450_600.append(abs(float(lines.split(" ")[4])))

#       with open('{}/higgsCombineTest.MultiDimFit.mH125_all_r_H_PTH_GT600.root_scan.txt'.format(args.InputDir),'r') as f:
       with open('{}/scan_r_H_{}_GT600.txt'.format(args.InputDir,VarName),'r') as f:
            lines=f.readline()
            ListOfLimit_GT600.append(float(lines.split(" ")[2]))
            ListOfLimit_GT600.append(abs(float(lines.split(" ")[3])))
            ListOfLimit_GT600.append(abs(float(lines.split(" ")[4])))



       ListOfLimit_All=[]
       ListOfLimit_All.append(ListOfLimit_0_350)
       ListOfLimit_All.append(ListOfLimit_350_450)
       ListOfLimit_All.append(ListOfLimit_450_600)
       ListOfLimit_All.append(ListOfLimit_GT600)
#       ListOfLimit_All.append(ListOfLimit_GT800)

       print ListOfLimit_0_350[0], ListOfLimit_350_450[0], ListOfLimit_450_600[0], ListOfLimit_GT600[0]
       print ListOfLimit_All[0][0], ListOfLimit_All[1][0], ListOfLimit_All[2][0], ListOfLimit_All[3][0]


       if k==0:#HpT
          xList = [300,400,525,1300]
          xhighList = [50,50,75,700]
          xlowList = [50,50,75,700]
          
          yList = [
                   ListOfLimit_All[0][0] * ggH_nnlops_RB.GetBinContent(1),
                   ListOfLimit_All[1][0] * ggH_nnlops_RB.GetBinContent(2),
                   ListOfLimit_All[2][0] * ggH_nnlops_RB.GetBinContent(3),
                   ListOfLimit_All[3][0] * ggH_nnlops_RB.GetBinContent(4),
          ]
          ylowList = [
                   abs((ListOfLimit_All[0][1])) * ggH_nnlops_RB.GetBinContent(1),
                   abs((ListOfLimit_All[1][1])) * ggH_nnlops_RB.GetBinContent(2),
                   abs((ListOfLimit_All[2][1])) * ggH_nnlops_RB.GetBinContent(3),
                   abs((ListOfLimit_All[3][1])) * ggH_nnlops_RB.GetBinContent(4),
          ]
          yhighList =[
          
                   abs((ListOfLimit_All[0][2])) * ggH_nnlops_RB.GetBinContent(1),
                   abs((ListOfLimit_All[1][2])) * ggH_nnlops_RB.GetBinContent(2),
                   abs((ListOfLimit_All[2][2])) * ggH_nnlops_RB.GetBinContent(3),
                   abs((ListOfLimit_All[3][2])) * ggH_nnlops_RB.GetBinContent(4),
          ]
          
          print  ListOfLimit_All[0][0], (ListOfLimit_All[0][0]- ListOfLimit_All[0][1]), (-ListOfLimit_All[0][0]+ ListOfLimit_All[0][2])

          print "pth: ",ggH_nnlops_RB.GetBinContent(1)*ggH_nnlops_RB.GetBinWidth(1),ggH_nnlops_RB.GetBinContent(2)*ggH_nnlops_RB.GetBinWidth(2),ggH_nnlops_RB.GetBinContent(3)*ggH_nnlops_RB.GetBinWidth(3),ggH_nnlops_RB.GetBinContent(4)*ggH_nnlops_RB.GetBinWidth(4),ggH_nnlops_RB.GetBinContent(5)*ggH_nnlops_RB.GetBinWidth(5),ggH_nnlops_RB.GetBinContent(6)*ggH_nnlops_RB.GetBinWidth(6),ggH_nnlops_RB.GetBinContent(7)*ggH_nnlops_RB.GetBinWidth(7)
          print "pth err: ",ggH_nnlops_RB.GetBinError(1)*ggH_nnlops_RB.GetBinWidth(1),ggH_nnlops_RB.GetBinError(2)*ggH_nnlops_RB.GetBinWidth(2),ggH_nnlops_RB.GetBinError(3)*ggH_nnlops_RB.GetBinWidth(3),ggH_nnlops_RB.GetBinError(4)*ggH_nnlops_RB.GetBinWidth(4),ggH_nnlops_RB.GetBinError(5)*ggH_nnlops_RB.GetBinWidth(5),ggH_nnlops_RB.GetBinError(6)*ggH_nnlops_RB.GetBinWidth(6),ggH_nnlops_RB.GetBinError(7)*ggH_nnlops_RB.GetBinWidth(7)

       if k==1:
          xList = [175,400,525,1300]
          xhighList = [175,50,75,700]
          xlowList = [175,50,75,700]

          yList = [
                   ListOfLimit_All[0][0] * ggH_nnlops_RB.GetBinContent(1),
                   ListOfLimit_All[1][0] * ggH_nnlops_RB.GetBinContent(2),
                   ListOfLimit_All[2][0] * ggH_nnlops_RB.GetBinContent(3),
                   ListOfLimit_All[3][0] * ggH_nnlops_RB.GetBinContent(4),
          ]
          ylowList = [
                   abs((ListOfLimit_All[0][1])) * ggH_nnlops_RB.GetBinContent(1),
                   abs((ListOfLimit_All[1][1])) * ggH_nnlops_RB.GetBinContent(2),
                   abs((ListOfLimit_All[2][1])) * ggH_nnlops_RB.GetBinContent(3),
                   abs((ListOfLimit_All[3][1])) * ggH_nnlops_RB.GetBinContent(4),
          ]
          yhighList =[
          
                   abs((ListOfLimit_All[0][2])) * ggH_nnlops_RB.GetBinContent(1),
                   abs((ListOfLimit_All[1][2])) * ggH_nnlops_RB.GetBinContent(2),
                   abs((ListOfLimit_All[2][2])) * ggH_nnlops_RB.GetBinContent(3),
                   abs((ListOfLimit_All[3][2])) * ggH_nnlops_RB.GetBinContent(4),
          ]


          print "ljpt: ",ggH_nnlops_RB.GetBinContent(1)*ggH_nnlops_RB.GetBinWidth(1),ggH_nnlops_RB.GetBinContent(2)*ggH_nnlops_RB.GetBinWidth(2),ggH_nnlops_RB.GetBinContent(3)*ggH_nnlops_RB.GetBinWidth(3),ggH_nnlops_RB.GetBinContent(4)*ggH_nnlops_RB.GetBinWidth(4),ggH_nnlops_RB.GetBinContent(5)*ggH_nnlops_RB.GetBinWidth(5)
          print "ljpt err: ",ggH_nnlops_RB.GetBinError(1)*ggH_nnlops_RB.GetBinWidth(1),ggH_nnlops_RB.GetBinError(2)*ggH_nnlops_RB.GetBinWidth(2),ggH_nnlops_RB.GetBinError(3)*ggH_nnlops_RB.GetBinWidth(3),ggH_nnlops_RB.GetBinError(4)*ggH_nnlops_RB.GetBinWidth(4),ggH_nnlops_RB.GetBinError(5)*ggH_nnlops_RB.GetBinWidth(5)

       x = array.array('d', xList)
       y = array.array('d', yList)
       xhigh = array.array('d', xhighList)
       yhigh = array.array('d', yhighList)
       xlow = array.array('d', xlowList)
       ylow = array.array('d', ylowList)
       Data = ROOT.TGraphAsymmErrors(len(x),x,y,xlow,xhigh,ylow,yhigh)
       Data.SetMarkerStyle(20)
       Data.SetMarkerColor(ROOT.kBlack)
       Data.SetMarkerSize(1)
       Data.GetXaxis().SetLimits(250,2000)
       Data.Draw("EP0SAME")
       pad1.Update()


       ggH_powheg_RB_line=ggH_powheg_RB.Clone()
       ggH_nnlops_RB_line=ggH_nnlops_RB.Clone()
       ggH_powheg_RB.SetFillStyle(3005)
       ggH_nnlops_RB.SetFillStyle(3004)
       ggH_powheg_RB.SetMarkerSize(0)
       ggH_powheg_RB.SetFillColor(ROOT.TColor.GetColor("#670178"))
       ggH_nnlops_RB.SetMarkerSize(0)
       ggH_nnlops_RB.SetFillColor(ROOT.TColor.GetColor("#137a63"))
       ggH_powheg_RB.GetXaxis().SetRangeUser(250,2000)
       ggH_nnlops_RB.GetXaxis().SetRangeUser(250,2000)
       ggH_powheg_RB.Draw("e2")
       ggH_nnlops_RB.Draw("e2same")
       ggH_powheg_RB_line.Draw("histsame")
       ggH_nnlops_RB_line.Draw("histsame")
       XH.Draw("histsame")
       Data.Draw("EP0SAME")
       pad1.Update()

       fidxs=0.
       for cc in range(1,ggH_powheg_RB.GetSize()-1):
         fidxs=fidxs+ggH_nnlops_RB.GetBinContent(cc)*ggH_nnlops_RB.GetBinWidth(cc)
       print fidxs
       
       legende=make_legend()
       legende.AddEntry(Data,"Observed","ep")
       legende.AddEntry(ggH_powheg_RB,"gg#rightarrowH (POWHEG) + XH","lf")
       legende.AddEntry(ggH_nnlops_RB,"gg#rightarrowH (NNLOPS) + XH","lf")
       legende.AddEntry(XH,"XH = VBF + VH + ttH (POWHEG)","f")
       legende.Draw()

       lumi1=add_CMS()
       lumi1.Draw("same")
       lumi2=add_lumiall()
       lumi2.Draw("same")
       lumi8=add_Preliminary()
       lumi8.Draw("same")

       lumi3  = ROOT.TPaveText(0.12, 0.835+0.06, 0.65, 0.835+0.16, "NDC")
       lumi3.SetBorderSize(   0 )
       lumi3.SetFillStyle(    0 )
       lumi3.SetTextAlign(   12 )
       lumi3.SetTextColor(    1 )
       lumi3.SetTextSize(0.05)
       lumi3.SetTextFont (   42 )
       lumi3.Draw("same")
       
       pad1.RedrawAxis()
       
       c.cd()
       pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
       pad2.SetTopMargin(0.05);
       pad2.SetBottomMargin(0.35);
       pad2.SetLeftMargin(0.18);
       pad2.SetRightMargin(0.05);
       pad2.SetTickx(1)
       pad2.SetTicky(1)
       #pad2.SetGridx()
       pad2.SetGridy()
       pad2.Draw()
       pad2.cd()

       hwoError=ggH_nnlops_RB.Clone()
       for z in range(1,hwoError.GetSize()-1):
         hwoError.SetBinError(z,0)
       h1=ggH_powheg_RB.Clone()
       h2=ggH_nnlops_RB.Clone()
       h1.Divide(hwoError)
       h2.Divide(hwoError)
       errorBand1 = h1.Clone()
       errorBand2 = h2.Clone()

       h1.GetXaxis().SetLimits(250,2000)
       h1.GetXaxis().SetTitle(xaxis[k])
       if k==4:
         h1.GetXaxis().SetBinLabel(1,"e#mu")
         h1.GetXaxis().SetBinLabel(2,"e#tau_{h}")
         h1.GetXaxis().SetBinLabel(3,"#mu#tau_{h}")
         h1.GetXaxis().SetBinLabel(4,"#tau_{h}#tau_{h}")
       h1.GetXaxis().SetLabelSize(0.08)
       h1.GetYaxis().SetLabelSize(0.08)
       h1.GetYaxis().SetTitle("Ratio to NNLOPS")
       h1.GetXaxis().SetNdivisions(505)
       h1.GetYaxis().SetNdivisions(5)
       h1.SetTitle("")
       h1.GetXaxis().SetTitleSize(0.15)
       h1.GetYaxis().SetTitleSize(0.10)
       h1.GetYaxis().SetTitleOffset(0.86)
       h1.GetXaxis().SetTitleOffset(0.94)
       h1.GetXaxis().SetLabelSize(0.11)
       h1.GetYaxis().SetLabelSize(0.11)
       h1.GetXaxis().SetTitleFont(42)
       h1.GetYaxis().SetTitleFont(42)
       h1.GetXaxis().SetLimits(250,2000)
       h1.SetMaximum(2.0)
       h1.SetMinimum(0)
       if "p_" in xaxis[k] and "j" not in xaxis[k]:
         h1.SetMinimum(-2.01)
         h1.SetMaximum(5)
       if "j_" in xaxis[k]:
         h1.SetMinimum(-2.01)
         h1.SetMaximum(5)
         
       h1.SetFillStyle(0)
       h1.Draw("hist")

       errorBand1.SetMarkerSize(0)
       errorBand1.SetFillColor(1)
       errorBand1.SetLineColor(ROOT.TColor.GetColor("#670178"))
       errorBand1.SetFillColor(ROOT.TColor.GetColor("#670178"))
       errorBand1.SetFillStyle(3005)
       errorBand1.GetXaxis().SetLimits(250,2000)
       errorBand1.Draw("e2same")
       errorBand1.Draw("e2same")

       errorBand2.SetMarkerSize(0)
       errorBand2.SetFillColor(1)
       errorBand2.SetLineColor(ROOT.TColor.GetColor("#137a63"))
       errorBand2.SetFillColor(ROOT.TColor.GetColor("#137a63"))
       errorBand2.SetFillStyle(3004)
       errorBand2.GetXaxis().SetLimits(250,2000)
       errorBand2.Draw("e2same")

       yList2=yList
       yhighList2=yhighList
       ylowList2=ylowList
       for z in range(0,hwoError.GetSize()-2):
         if z > 3: break
         print 'zi is ', z
         yList2[z]=yList[z]/hwoError.GetBinContent(z+1)
         ylowList2[z]=ylowList[z]/hwoError.GetBinContent(z+1)
         yhighList2[z]=yhighList[z]/hwoError.GetBinContent(z+1)

       y2 = array.array('d', yList2)
       yhigh2 = array.array('d', yhighList2)
       ylow2 = array.array('d', ylowList2)
       Data2 = ROOT.TGraphAsymmErrors(len(x),x,y2,xlow,xhigh,ylow2,yhigh2)
       Data2.SetMarkerStyle(20)
       Data2.SetMarkerColor(ROOT.kBlack)
       Data2.SetMarkerSize(1)
       Data2.GetXaxis().SetLimits(250,2000)

       pad2.Update()
       Data2.Draw("EP0SAME")

       if "p_" in xaxis[k] and "j" not in xaxis[k]:
         mybox=ROOT.TBox(0,-0.5,550,0)
         mybox.SetFillStyle(3011)
         mybox.SetLineColor(1)
         mybox.SetFillColor(1)
#         mybox.Draw("same")

       if "p_" in xaxis[k] and "j" in xaxis[k]:
         mybox=ROOT.TBox(0,-0.5,400,0)
         mybox.SetFillStyle(3011)
         mybox.SetLineColor(1)
         mybox.SetFillColor(1)
#         mybox.Draw("same")

       pad2.Update()
       
       c.cd()
       pad1.Draw()
       
       ROOT.gPad.RedrawAxis()
       
       c.Modified()
       c.SaveAs("differential_"+args.OutName+"_"+variable[k]+"_unblind.pdf")
    #   c.SaveAs("differential_v3_"+variable[k]+"_v2.png")
       
   


if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--TheoryInput', '-i', required=True, help='Theory Input file where the fiducial custa re defined')
    parser.add_argument('--InputDir', '-g', required=True, help='Location of the scan.txt files')
    parser.add_argument('--JetPtLimit', '-j', required=True, help='Higgs Combine outcome of jet pT')
    parser.add_argument('--OutName', '-o', required=True, help='OutName')
    
    main(parser.parse_args())
