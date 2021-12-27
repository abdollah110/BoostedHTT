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
    lumi.SetTextSize(0.08)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("CMS")
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
        output = ROOT.TLegend(0.35, 0.62, 0.96, 0.86, "", "brNDC")
        output.SetLineWidth(0)
        output.SetLineStyle(0)
        output.SetFillStyle(0)
        output.SetBorderSize(0)
 	output.SetNColumns(1)
        output.SetTextFont(62)
        return output

ROOT.gStyle.SetOptStat(0)
#ROOT.gStyle.SetErrorX(0)

c=ROOT.TCanvas("canvas","",0,0,600,600)
c.cd()

file=ROOT.TFile("differential_theory.root","r")

adapt=ROOT.gROOT.GetColor(12)
new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

nvar=1
#variable=["njets","mjj","hpt","jpt","fs"]
#xaxis=["N_{jets}","m_{jj} (GeV)","p_{T}^{H} (GeV)","p_{T}^{j_{1}} (GeV)","Final state"]
#yaxis=["#sigma_{fid} (fb)","d#sigma_{fid}/dm_{jj} (fb/GeV)","d#sigma_{fid}/dp_{T}(H) (fb/GeV)","d#sigma_{fid}/dp_{T}(jet) (fb/GeV)","#sigma_{fid} (fb)"]
variable=["hpt"]
xaxis=["p_{T}^{H} (GeV)"]
yaxis=["d#sigma_{fid}/dp_{T}(H) (fb/GeV)"]
postfix=["_THU_ggH_Mu","_THU_ggH_Res","_THU_ggH_Mig01","_THU_ggH_Mig12","_THU_ggH_VBF2j","_THU_ggH_VBF3j","_THU_ggH_PT60","_THU_ggH_PT120","_THU_ggH_qmtop"]

for k in range(0,nvar):

   ggH_count=file.Get(variable[k]+"_nnlops").Get("ggH_htt125")
   xs=[0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]
   for j in range(1,ggH_count.GetSize()-1):
     xs[0]=xs[0]+ggH_count.GetBinContent(j)
     xs[0]=xs[0]+file.Get(variable[k]+"_powheg").Get("qqH_htt125").GetBinContent(j)
     xs[0]=xs[0]+file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125").GetBinContent(j)
     xs[0]=xs[0]+file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125").GetBinContent(j)
     xs[0]=xs[0]+file.Get(variable[k]+"_powheg").Get("WH_htt125").GetBinContent(j)
     xs[0]=xs[0]+file.Get(variable[k]+"_powheg").Get("ZH_htt125").GetBinContent(j)
     xs[0]=xs[0]+file.Get(variable[k]+"_powheg").Get("ttH_htt125").GetBinContent(j)
     for z in range(0,9):
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_nnlops").Get("ggH_htt125"+postfix[z]).GetBinContent(j)
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_powheg").Get("qqH_htt125").GetBinContent(j)
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125").GetBinContent(j)
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125").GetBinContent(j)
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_powheg").Get("WH_htt125").GetBinContent(j)
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_powheg").Get("ZH_htt125").GetBinContent(j)
        xs[z+1]=xs[z+1]+file.Get(variable[k]+"_powheg").Get("ttH_htt125").GetBinContent(j)

     xs[10]=xs[10]+ggH_count.GetBinContent(j)
     xs[10]=xs[10]+file.Get(variable[k]+"_powheg").Get("qqH_htt125_scale").GetBinContent(j)
     xs[10]=xs[10]+file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125").GetBinContent(j)
     xs[10]=xs[10]+file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125").GetBinContent(j)
     xs[10]=xs[10]+file.Get(variable[k]+"_powheg").Get("WH_htt125").GetBinContent(j)
     xs[10]=xs[10]+file.Get(variable[k]+"_powheg").Get("ZH_htt125").GetBinContent(j)
     xs[10]=xs[10]+file.Get(variable[k]+"_powheg").Get("ttH_htt125").GetBinContent(j)

     xs[11]=xs[11]+ggH_count.GetBinContent(j)
     xs[11]=xs[11]+file.Get(variable[k]+"_powheg").Get("qqH_htt125").GetBinContent(j)
     xs[11]=xs[11]+file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125").GetBinContent(j)
     xs[11]=xs[11]+file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125").GetBinContent(j)
     xs[11]=xs[11]+file.Get(variable[k]+"_powheg").Get("WH_htt125_scale").GetBinContent(j)
     xs[11]=xs[11]+file.Get(variable[k]+"_powheg").Get("ZH_htt125").GetBinContent(j)
     xs[11]=xs[11]+file.Get(variable[k]+"_powheg").Get("ttH_htt125").GetBinContent(j)

     xs[12]=xs[12]+ggH_count.GetBinContent(j)
     xs[12]=xs[12]+file.Get(variable[k]+"_powheg").Get("qqH_htt125").GetBinContent(j)
     xs[12]=xs[12]+file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125_scale").GetBinContent(j)
     xs[12]=xs[12]+file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125_scale").GetBinContent(j)
     xs[12]=xs[12]+file.Get(variable[k]+"_powheg").Get("WH_htt125").GetBinContent(j)
     xs[12]=xs[12]+file.Get(variable[k]+"_powheg").Get("ZH_htt125_scale").GetBinContent(j)
     xs[12]=xs[12]+file.Get(variable[k]+"_powheg").Get("ttH_htt125").GetBinContent(j)

     xs[13]=xs[13]+ggH_count.GetBinContent(j)
     xs[13]=xs[13]+file.Get(variable[k]+"_powheg").Get("qqH_htt125").GetBinContent(j)
     xs[13]=xs[13]+file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125").GetBinContent(j)
     xs[13]=xs[13]+file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125").GetBinContent(j)
     xs[13]=xs[13]+file.Get(variable[k]+"_powheg").Get("WH_htt125").GetBinContent(j)
     xs[13]=xs[13]+file.Get(variable[k]+"_powheg").Get("ZH_htt125").GetBinContent(j)
     xs[13]=xs[13]+file.Get(variable[k]+"_powheg").Get("ttH_htt125_scale").GetBinContent(j)

   xs_scale_2=0.0
   for gg in range(0,13):
     xs_scale_2=xs_scale_2+(xs[0]-xs[gg+1])*(xs[0]-xs[gg+1])
   xs_scale_2=xs_scale_2+(0.0206*0.0206*xs[0]*xs[0]) # BR tau
   xs_scale_2=xs_scale_2+(0.03*0.03*xs[0]*xs[0]) # PDF
   print "xs ",1000*xs[0],1000*(xs_scale_2**0.5)


   ggH_powheg=file.Get(variable[k]+"_powheg").Get("ggH_htt125")
   for j in range(1,ggH_powheg.GetSize()-1):
     ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.0206*0.0206*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #BR tau
     ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.032*0.032*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #PDF gg
     if k==0 and j==2: #1 jet
          ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.025*0.025*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #Pythia scale
     if k==0 and j==3: #2 jets
          ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.05*0.05*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #Pythia scale
     if k==0 and j>3: #2 jets
          ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+0.10*0.10*ggH_powheg.GetBinContent(j)*ggH_powheg.GetBinContent(j))**0.5) #Pythia scale

     for z in range(0,9):
         ggH_powheg_alternative=file.Get(variable[k]+"_powheg").Get("ggH_htt125"+postfix[z])
         unc=abs(ggH_powheg_alternative.GetBinContent(j)-ggH_powheg.GetBinContent(j))
         ggH_powheg.SetBinError(j,(ggH_powheg.GetBinError(j)*ggH_powheg.GetBinError(j)+unc*unc)**0.5)

   ggH_nnlops=file.Get(variable[k]+"_nnlops").Get("ggH_htt125")
   ggH_nnlops_em=file.Get("njets_nnlops_em").Get("ggH_htt125")
   ggH_nnlops_et=file.Get("njets_nnlops_et").Get("ggH_htt125")
   ggH_nnlops_mt=file.Get("njets_nnlops_mt").Get("ggH_htt125")
   ggH_nnlops_tt=file.Get("njets_nnlops_tt").Get("ggH_htt125")
   for j in range(1,ggH_powheg.GetSize()-1):
     ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.0206*0.0206*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) # BR tau
     ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.032*0.032*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) # PDF gg
     if k==0 and j==2: #1 jet 
          ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.025*0.025*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) #Pythia scale
     if k==0 and j==3: #2 jets
          ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.05*0.05*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) #Pythia scale
     if k==0 and j>3: #2 jets
          ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+0.10*0.10*ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinContent(j))**0.5) #Pythia scale

     for z in range(0,9):
         ggH_nnlops_alternative=file.Get(variable[k]+"_nnlops").Get("ggH_htt125"+postfix[z])
         unc=abs(ggH_nnlops_alternative.GetBinContent(j)-ggH_nnlops.GetBinContent(j))
         ggH_nnlops.SetBinError(j,(ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinError(j)+unc*unc)**0.5)
    
   for j in range(1,ggH_powheg.GetSize()-1):
     print ggH_nnlops.GetBinContent(j)*ggH_nnlops.GetBinWidth(j),ggH_nnlops.GetBinError(j)*ggH_nnlops.GetBinWidth(j)

   qqH=file.Get(variable[k]+"_powheg").Get("qqH_htt125")
   WH=file.Get(variable[k]+"_powheg").Get("WH_htt125")
   ZH=file.Get(variable[k]+"_powheg").Get("ZH_htt125")
   ggZH_lep=file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125")
   ggZH_had=file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125")
   ttH=file.Get(variable[k]+"_powheg").Get("ttH_htt125")

   qqH_em=file.Get("njets_powheg_em").Get("qqH_htt125")
   WH_em=file.Get("njets_powheg_em").Get("WH_htt125")
   ZH_em=file.Get("njets_powheg_em").Get("ZH_htt125")
   ggZH_lep_em=file.Get("njets_powheg_em").Get("ggZH_lep_htt125")
   ggZH_had_em=file.Get("njets_powheg_em").Get("ggZH_had_htt125")
   ttH_em=file.Get("njets_powheg_em").Get("ttH_htt125")

   qqH_et=file.Get("njets_powheg_et").Get("qqH_htt125")
   WH_et=file.Get("njets_powheg_et").Get("WH_htt125")
   ZH_et=file.Get("njets_powheg_et").Get("ZH_htt125")
   ggZH_lep_et=file.Get("njets_powheg_et").Get("ggZH_lep_htt125")
   ggZH_had_et=file.Get("njets_powheg_et").Get("ggZH_had_htt125")
   ttH_et=file.Get("njets_powheg_et").Get("ttH_htt125")

   qqH_mt=file.Get("njets_powheg_mt").Get("qqH_htt125")
   WH_mt=file.Get("njets_powheg_mt").Get("WH_htt125")
   ZH_mt=file.Get("njets_powheg_mt").Get("ZH_htt125")
   ggZH_lep_mt=file.Get("njets_powheg_mt").Get("ggZH_lep_htt125")
   ggZH_had_mt=file.Get("njets_powheg_mt").Get("ggZH_had_htt125")
   ttH_mt=file.Get("njets_powheg_mt").Get("ttH_htt125")

   qqH_tt=file.Get("njets_powheg_tt").Get("qqH_htt125")
   WH_tt=file.Get("njets_powheg_tt").Get("WH_htt125")
   ZH_tt=file.Get("njets_powheg_tt").Get("ZH_htt125")
   ggZH_lep_tt=file.Get("njets_powheg_tt").Get("ggZH_lep_htt125")
   ggZH_had_tt=file.Get("njets_powheg_tt").Get("ggZH_had_htt125")
   ttH_tt=file.Get("njets_powheg_tt").Get("ttH_htt125")

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

      qqH_alternative=file.Get(variable[k]+"_powheg").Get("qqH_htt125_scale")
      unc=abs(qqH_alternative.GetBinContent(j)-qqH.GetBinContent(j))
      qqH.SetBinError(j,(qqH.GetBinError(j)*qqH.GetBinError(j)+unc*unc)**0.5)

      WH_alternative=file.Get(variable[k]+"_powheg").Get("WH_htt125_scale")
      unc=abs(WH_alternative.GetBinContent(j)-WH.GetBinContent(j))
      WH.SetBinError(j,(WH.GetBinError(j)*WH.GetBinError(j)+unc*unc)**0.5)

      ZH_alternative=file.Get(variable[k]+"_powheg").Get("ZH_htt125_scale")
      unc=abs(ZH_alternative.GetBinContent(j)-ZH.GetBinContent(j))
      ZH.SetBinError(j,(ZH.GetBinError(j)*ZH.GetBinError(j)+unc*unc)**0.5)

      ggZH_lep_alternative=file.Get(variable[k]+"_powheg").Get("ggZH_lep_htt125_scale")
      unc=abs(ggZH_lep_alternative.GetBinContent(j)-ggZH_lep.GetBinContent(j))
      ggZH_lep.SetBinError(j,(ggZH_lep.GetBinError(j)*ggZH_lep.GetBinError(j)+unc*unc)**0.5)

      ggZH_had_alternative=file.Get(variable[k]+"_powheg").Get("ggZH_had_htt125_scale")
      unc=abs(ggZH_had_alternative.GetBinContent(j)-ggZH_had.GetBinContent(j))
      ggZH_had.SetBinError(j,(ggZH_had.GetBinError(j)*ggZH_had.GetBinError(j)+unc*unc)**0.5)

      ttH_alternative=file.Get(variable[k]+"_powheg").Get("ttH_htt125_scale")
      unc=abs(ttH_alternative.GetBinContent(j)-ttH.GetBinContent(j))
      ttH.SetBinError(j,(ttH.GetBinError(j)*ttH.GetBinError(j)+unc*unc)**0.5)

   XH=WH.Clone()
   XH.Add(ZH)
   XH.Add(qqH)
   XH.Add(ggZH_lep)
   XH.Add(ggZH_had)
   XH.Add(ttH)

   XH_em=WH_em.Clone()
   XH_em.Add(ZH_em)
   XH_em.Add(qqH_em)
   XH_em.Add(ggZH_lep_em)
   XH_em.Add(ggZH_had_em)
   XH_em.Add(ttH_em)

   XH_et=WH_et.Clone()
   XH_et.Add(ZH_et)
   XH_et.Add(qqH_et)
   XH_et.Add(ggZH_lep_et)
   XH_et.Add(ggZH_had_et)
   XH_et.Add(ttH_et)

   XH_mt=WH_mt.Clone()
   XH_mt.Add(ZH_mt)
   XH_mt.Add(qqH_mt)
   XH_mt.Add(ggZH_lep_mt)
   XH_mt.Add(ggZH_had_mt)
   XH_mt.Add(ttH_mt)

   XH_tt=WH_tt.Clone()
   XH_tt.Add(ZH_tt)
   XH_tt.Add(qqH_tt)
   XH_tt.Add(ggZH_lep_tt)
   XH_tt.Add(ggZH_had_tt)
   XH_tt.Add(ttH_tt)

   ggH_powheg.Add(XH)
   ggH_nnlops.Add(XH)
   ggH_nnlops_em.Add(XH_em)
   ggH_nnlops_et.Add(XH_et)
   ggH_nnlops_mt.Add(XH_mt)
   ggH_nnlops_tt.Add(XH_tt)

   for j in range(0,ggH_powheg.GetSize()-2):
     width=ggH_powheg.GetBinWidth(j+1)
     ggH_powheg.SetBinContent(j+1,ggH_powheg.GetBinContent(j+1)*1000/width)
     ggH_nnlops.SetBinContent(j+1,ggH_nnlops.GetBinContent(j+1)*1000/width)
     XH.SetBinContent(j+1,XH.GetBinContent(j+1)*1000/width)
     ggH_nnlops_em.SetBinContent(j+1,ggH_nnlops_em.GetBinContent(j+1)*1000/width)
     XH_em.SetBinContent(j+1,XH_em.GetBinContent(j+1)*1000/width)
     ggH_nnlops_et.SetBinContent(j+1,ggH_nnlops_et.GetBinContent(j+1)*1000/width)
     XH_et.SetBinContent(j+1,XH_et.GetBinContent(j+1)*1000/width)
     ggH_nnlops_mt.SetBinContent(j+1,ggH_nnlops_mt.GetBinContent(j+1)*1000/width)
     XH_mt.SetBinContent(j+1,XH_mt.GetBinContent(j+1)*1000/width)
     ggH_nnlops_tt.SetBinContent(j+1,ggH_nnlops_tt.GetBinContent(j+1)*1000/width)
     XH_tt.SetBinContent(j+1,XH_tt.GetBinContent(j+1)*1000/width)
     ggH_powheg.SetBinError(j+1,ggH_powheg.GetBinError(j+1)*1000/width)
     ggH_nnlops.SetBinError(j+1,ggH_nnlops.GetBinError(j+1)*1000/width)
     XH.SetBinError(j+1,XH.GetBinError(j+1)*1000/width)
   
   ggH_powheg.GetXaxis().SetTitle("")
   ggH_powheg.GetXaxis().SetTitleSize(0)
   ggH_powheg.GetXaxis().SetNdivisions(505)
   ggH_powheg.GetYaxis().SetLabelFont(42)
   ggH_powheg.GetYaxis().SetLabelOffset(0.01)
   ggH_powheg.GetYaxis().SetLabelSize(0.06)
   ggH_powheg.GetYaxis().SetTitleSize(0.075)
   ggH_powheg.GetYaxis().SetTitleOffset(1.04)
   ggH_powheg.SetTitle("")
   ggH_powheg.GetYaxis().SetTitle(yaxis[k])
   #ggH_powheg.SetMinimum(0.1)
   if k<4: ggH_powheg.SetMinimum(ggH_powheg.GetBinContent(ggH_powheg.GetSize()-2)/10)
   if k<4: ggH_powheg.SetMaximum(7*ggH_powheg.GetMaximum())
   if k==4: ggH_powheg.SetMinimum(0)
   if k==4: ggH_powheg.SetMaximum(2*ggH_powheg.GetMaximum())
   if k==0: ggH_powheg.SetMaximum(2*ggH_powheg.GetMaximum())
   ggH_powheg.SetMarkerStyle(20)
   ggH_powheg.SetMarkerSize(1)
   ggH_powheg.GetXaxis().SetLabelSize(0)
   
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

   #ggH_powheg.SetLineColor(2)
   #ggH_nnlops.SetLineColor(3)
   #XH.SetFillColor(4)

   ggH_powheg.SetLineColor(ROOT.TColor.GetColor("#9999cc"))
   ggH_nnlops.SetLineColor(ROOT.TColor.GetColor("#12cadd"))
   XH.SetFillColor(ROOT.TColor.GetColor("#ffcc66"))
   XH.SetLineColor(ROOT.TColor.GetColor("#ffcc66"))
   ggH_powheg.SetLineWidth(3)
   ggH_nnlops.SetLineWidth(3)

   xList = [1,2,3,4,0,0,0,0,0]
   yList = [1,4,9,16,0,0,0,0,0]
   xhighList = [0,0,0,0,0,0,0,0,0]
   yhighList = [1+1,4+1,9+1,16+1,0,0,0,0,0]
   xlowList = [0,0,0,0,0,0,0,0,0]
   ylowList = [1-1,4-1,9-1,16-1,0,0,0,0,0]

   if k==0:#njets
      xList = [0.5,1.5,2.5,3.5,4.5,5.5]
      xhighList = [0,0,0,0,0]
      xlowList = [0,0,0,0,0]
      yList = [1.25 * ggH_nnlops.GetBinContent(1),
               1.00 * ggH_nnlops.GetBinContent(2),
               0.84 * ggH_nnlops.GetBinContent(3),
               0.58 * ggH_nnlops.GetBinContent(4),
               0.57 * ggH_nnlops.GetBinContent(5)
      ]
      ylowList = [0.48 * ggH_nnlops.GetBinContent(1),
                  0.27 * ggH_nnlops.GetBinContent(2),
                  0.22 * ggH_nnlops.GetBinContent(3),
                  0.36 * ggH_nnlops.GetBinContent(4),
                  0.45 * ggH_nnlops.GetBinContent(5)
      ]
      yhighList = [0.47 * ggH_nnlops.GetBinContent(1),
                   0.28 * ggH_nnlops.GetBinContent(2),
                   0.22 * ggH_nnlops.GetBinContent(3),
                   0.36 * ggH_nnlops.GetBinContent(4),
                   0.46 * ggH_nnlops.GetBinContent(5)
      ]
      print "njets: ",ggH_nnlops.GetBinContent(1)*ggH_nnlops.GetBinWidth(1),ggH_nnlops.GetBinContent(2)*ggH_nnlops.GetBinWidth(2),ggH_nnlops.GetBinContent(3)*ggH_nnlops.GetBinWidth(3),ggH_nnlops.GetBinContent(4)*ggH_nnlops.GetBinWidth(4),ggH_nnlops.GetBinContent(5)*ggH_nnlops.GetBinWidth(5)
      print "njets err: ",ggH_nnlops.GetBinError(1)*ggH_nnlops.GetBinWidth(1),ggH_nnlops.GetBinError(2)*ggH_nnlops.GetBinWidth(2),ggH_nnlops.GetBinError(3)*ggH_nnlops.GetBinWidth(3),ggH_nnlops.GetBinError(4)*ggH_nnlops.GetBinWidth(4),ggH_nnlops.GetBinError(5)*ggH_nnlops.GetBinWidth(5)
      print "njets em: ",ggH_nnlops_em.GetBinContent(1)*ggH_nnlops_em.GetBinWidth(1),ggH_nnlops_em.GetBinContent(2)*ggH_nnlops_em.GetBinWidth(2),ggH_nnlops_em.GetBinContent(3)*ggH_nnlops_em.GetBinWidth(3),ggH_nnlops_em.GetBinContent(4)*ggH_nnlops_em.GetBinWidth(4),ggH_nnlops_em.GetBinContent(5)*ggH_nnlops_em.GetBinWidth(5)
      print "njets et: ",ggH_nnlops_et.GetBinContent(1)*ggH_nnlops_et.GetBinWidth(1),ggH_nnlops_et.GetBinContent(2)*ggH_nnlops_et.GetBinWidth(2),ggH_nnlops_et.GetBinContent(3)*ggH_nnlops_et.GetBinWidth(3),ggH_nnlops_et.GetBinContent(4)*ggH_nnlops_et.GetBinWidth(4),ggH_nnlops_et.GetBinContent(5)*ggH_nnlops_et.GetBinWidth(5)
      print "njets mt: ",ggH_nnlops_mt.GetBinContent(1)*ggH_nnlops_mt.GetBinWidth(1),ggH_nnlops_mt.GetBinContent(2)*ggH_nnlops_mt.GetBinWidth(2),ggH_nnlops_mt.GetBinContent(3)*ggH_nnlops_mt.GetBinWidth(3),ggH_nnlops_mt.GetBinContent(4)*ggH_nnlops_mt.GetBinWidth(4),ggH_nnlops_mt.GetBinContent(5)*ggH_nnlops_mt.GetBinWidth(5)
      print "njets tt: ",ggH_nnlops_tt.GetBinContent(1)*ggH_nnlops_tt.GetBinWidth(1),ggH_nnlops_tt.GetBinContent(2)*ggH_nnlops_tt.GetBinWidth(2),ggH_nnlops_tt.GetBinContent(3)*ggH_nnlops_tt.GetBinWidth(3),ggH_nnlops_tt.GetBinContent(4)*ggH_nnlops_tt.GetBinWidth(4),ggH_nnlops_tt.GetBinContent(5)*ggH_nnlops_tt.GetBinWidth(5)

   if k==2:#HpT
      xList = [22.5,62.5,100,160,275,400,500]
      xhighList = [22.5,17.5,20,40,75,50,50]
      xlowList = [22.5,17.5,20,40,75,50,50]
      yList = [0.11 * ggH_nnlops.GetBinContent(1),
               0.34 * ggH_nnlops.GetBinContent(2),
               1.28 * ggH_nnlops.GetBinContent(3),
               1.18 * ggH_nnlops.GetBinContent(4),
               1.18 * ggH_nnlops.GetBinContent(5),
               1.68 * ggH_nnlops.GetBinContent(6),
               2.00 * ggH_nnlops.GetBinContent(7)
      ]
      ylowList = [0.44 * ggH_nnlops.GetBinContent(1),
                  0.45 * ggH_nnlops.GetBinContent(2),
                  0.40 * ggH_nnlops.GetBinContent(3),
                  0.26 * ggH_nnlops.GetBinContent(4),
                  0.36 * ggH_nnlops.GetBinContent(5),
                  0.59 * ggH_nnlops.GetBinContent(6),
                  0.85 * ggH_nnlops.GetBinContent(7)
      ]
      yhighList = [0.43 * ggH_nnlops.GetBinContent(1),
                   0.46 * ggH_nnlops.GetBinContent(2),
                   0.43 * ggH_nnlops.GetBinContent(3),
                   0.26 * ggH_nnlops.GetBinContent(4),
                   0.41 * ggH_nnlops.GetBinContent(5),
                   0.67 * ggH_nnlops.GetBinContent(6),
                   1.02 * ggH_nnlops.GetBinContent(7)
      ]
      print "pth: ",ggH_nnlops.GetBinContent(1)*ggH_nnlops.GetBinWidth(1),ggH_nnlops.GetBinContent(2)*ggH_nnlops.GetBinWidth(2),ggH_nnlops.GetBinContent(3)*ggH_nnlops.GetBinWidth(3),ggH_nnlops.GetBinContent(4)*ggH_nnlops.GetBinWidth(4),ggH_nnlops.GetBinContent(5)*ggH_nnlops.GetBinWidth(5),ggH_nnlops.GetBinContent(6)*ggH_nnlops.GetBinWidth(6),ggH_nnlops.GetBinContent(7)*ggH_nnlops.GetBinWidth(7)
      print "pth err: ",ggH_nnlops.GetBinError(1)*ggH_nnlops.GetBinWidth(1),ggH_nnlops.GetBinError(2)*ggH_nnlops.GetBinWidth(2),ggH_nnlops.GetBinError(3)*ggH_nnlops.GetBinWidth(3),ggH_nnlops.GetBinError(4)*ggH_nnlops.GetBinWidth(4),ggH_nnlops.GetBinError(5)*ggH_nnlops.GetBinWidth(5),ggH_nnlops.GetBinError(6)*ggH_nnlops.GetBinWidth(6),ggH_nnlops.GetBinError(7)*ggH_nnlops.GetBinWidth(7)

   if k==3:#j1pt
      xList = [15,45,90,160,275,375]
      xhighList = [15,15,30,40,75,25]
      xlowList = [15,15,30,40,75,25]
      yList = [1.11 * ggH_nnlops.GetBinContent(1),
               0.24 * ggH_nnlops.GetBinContent(2),
               0.60 * ggH_nnlops.GetBinContent(3),
               1.13 * ggH_nnlops.GetBinContent(4),
               1.06 * ggH_nnlops.GetBinContent(5),
               1.30 * ggH_nnlops.GetBinContent(6)
      ]
      ylowList = [
                  0.50 * ggH_nnlops.GetBinContent(1),
                  0.41 * ggH_nnlops.GetBinContent(2),
                  0.27 * ggH_nnlops.GetBinContent(3),
                  0.25 * ggH_nnlops.GetBinContent(4),
                  0.34 * ggH_nnlops.GetBinContent(5),
                  0.63 * ggH_nnlops.GetBinContent(6)
      ]
      yhighList = [
                   0.50 * ggH_nnlops.GetBinContent(1),
                   0.42 * ggH_nnlops.GetBinContent(2),
                   0.27 * ggH_nnlops.GetBinContent(3),
                   0.26 * ggH_nnlops.GetBinContent(4),
                   0.38 * ggH_nnlops.GetBinContent(5),
                   0.72 * ggH_nnlops.GetBinContent(6)
      ]
      print "ljpt: ",ggH_nnlops.GetBinContent(1)*ggH_nnlops.GetBinWidth(1),ggH_nnlops.GetBinContent(2)*ggH_nnlops.GetBinWidth(2),ggH_nnlops.GetBinContent(3)*ggH_nnlops.GetBinWidth(3),ggH_nnlops.GetBinContent(4)*ggH_nnlops.GetBinWidth(4),ggH_nnlops.GetBinContent(5)*ggH_nnlops.GetBinWidth(5),ggH_nnlops.GetBinContent(6)*ggH_nnlops.GetBinWidth(6)
      print "ljpt err: ",ggH_nnlops.GetBinError(1)*ggH_nnlops.GetBinWidth(1),ggH_nnlops.GetBinError(2)*ggH_nnlops.GetBinWidth(2),ggH_nnlops.GetBinError(3)*ggH_nnlops.GetBinWidth(3),ggH_nnlops.GetBinError(4)*ggH_nnlops.GetBinWidth(4),ggH_nnlops.GetBinError(5)*ggH_nnlops.GetBinWidth(5),ggH_nnlops.GetBinError(6)*ggH_nnlops.GetBinWidth(6)

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
   Data.Draw("EP0SAME")
   pad1.Update()


   ggH_powheg_line=ggH_powheg.Clone()
   ggH_nnlops_line=ggH_nnlops.Clone()
   ggH_powheg.SetFillStyle(3005)
   ggH_nnlops.SetFillStyle(3004)
   ggH_powheg.SetMarkerSize(0)
   ggH_powheg.SetFillColor(ROOT.TColor.GetColor("#670178"))
   ggH_nnlops.SetMarkerSize(0)
   ggH_nnlops.SetFillColor(ROOT.TColor.GetColor("#137a63"))
   ggH_powheg.Draw("e2")
   ggH_nnlops.Draw("e2same")
   ggH_powheg_line.Draw("histsame")
   ggH_nnlops_line.Draw("histsame")
   XH.Draw("histsame")
   Data.Draw("EP0SAME")
   pad1.Update()

   fidxs=0.
   for cc in range(1,ggH_powheg.GetSize()-1):
     fidxs=fidxs+ggH_nnlops.GetBinContent(cc)*ggH_nnlops.GetBinWidth(cc)
   print fidxs
   
   legende=make_legend()
   legende.AddEntry(Data,"Observed","ep")
   legende.AddEntry(ggH_powheg,"gg#rightarrowH (POWHEG) + XH","lf")
   legende.AddEntry(ggH_nnlops,"gg#rightarrowH (NNLOPS) + XH","lf")
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

   hwoError=ggH_nnlops.Clone()
   for z in range(1,hwoError.GetSize()-1):
     hwoError.SetBinError(z,0)
   h1=ggH_powheg.Clone()
   h2=ggH_nnlops.Clone()
   h1.Divide(hwoError)
   h2.Divide(hwoError)
   errorBand1 = h1.Clone()
   errorBand2 = h2.Clone()

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
   h1.SetMaximum(2.0)
   h1.SetMinimum(0)
   if "p_" in xaxis[k] and "j" not in xaxis[k]:
     h1.SetMinimum(-0.5)
     h1.SetMaximum(3.5)
   if "j_" in xaxis[k]:
     h1.SetMinimum(-0.5)
     h1.SetMaximum(2.2)
     
   h1.SetFillStyle(0)
   h1.Draw("hist")

   errorBand1.SetMarkerSize(0)
   errorBand1.SetFillColor(1)
   errorBand1.SetLineColor(ROOT.TColor.GetColor("#670178"))
   errorBand1.SetFillColor(ROOT.TColor.GetColor("#670178"))
   errorBand1.SetFillStyle(3005)
   errorBand1.Draw("e2same")

   errorBand2.SetMarkerSize(0)
   errorBand2.SetFillColor(1)
   errorBand2.SetLineColor(ROOT.TColor.GetColor("#137a63"))
   errorBand2.SetFillColor(ROOT.TColor.GetColor("#137a63"))
   errorBand2.SetFillStyle(3004)
   errorBand2.Draw("e2same")

   yList2=yList
   yhighList2=yhighList
   ylowList2=ylowList
   for z in range(0,hwoError.GetSize()-2):
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

   pad2.Update()
   Data2.Draw("EP0SAME")

   if "p_" in xaxis[k] and "j" not in xaxis[k]:
     mybox=ROOT.TBox(0,-0.5,550,0)
     mybox.SetFillStyle(3011)
     mybox.SetLineColor(1)
     mybox.SetFillColor(1)
     mybox.Draw("same")

   if "p_" in xaxis[k] and "j" in xaxis[k]:
     mybox=ROOT.TBox(0,-0.5,400,0)
     mybox.SetFillStyle(3011)
     mybox.SetLineColor(1)
     mybox.SetFillColor(1)
     mybox.Draw("same")

   pad2.Update()
   
   c.cd()
   pad1.Draw()
   
   ROOT.gPad.RedrawAxis()
   
   c.Modified()
   c.SaveAs("differential_"+variable[k]+".pdf")
   c.SaveAs("differential_"+variable[k]+".png")
   
   
