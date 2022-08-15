#!/usr/bin/env python
#for i in NewV3/postfit_shapes_NewV3_201* ; do python Draw_POSTPREFIT_Boost.py $i test1; done
#for i in em et mt tt; do for j in ztt signal qcd ; do hadd postfit_shapes_V12_newDMN_v2_rename_GIT_2020_${i}_${j}.root postfit_shapes_V12_newDMN_v2_rename_GIT_*_${i}_${j}.root ; done; done
import ROOT
import sys
import re
from array import array
import ROOT as rt

def add_lumi(year):
    lowX=0.67
    lowY=0.82
    lumi  = ROOT.TPaveText(lowX, lowY+0.04, lowX+0.30, lowY+0.14, "NDC")
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.SetTextSize(0.06)
    lumi.SetTextFont (   42 )
    if year==2016:
#        lumi.AddText("36.3 fb^{-1} (13 TeV)")
        lumi.AddText("138 fb^{-1} (13 TeV)")
    elif year==2017:
        lumi.AddText("41.5 fb^{-1} (13 TeV)")
    elif year==2018:
        lumi.AddText("59.7 fb^{-1} (13 TeV)")
    elif year==2020:
        lumi.AddText("138 fb^{-1} (13 TeV)")
    else :
        lumi.AddText(str(year))
#    lumi.AddText("77.4 fb^{-1} (13 TeV)")
    return lumi

def add_CMS():
    lowX=0.21
    lowY=0.70
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
    lowX=0.21
    lowY=0.63
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(52)
    lumi.SetTextSize(0.06)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText("Preliminary")
    return lumi

def make_legend():
    output = ROOT.TLegend(0.38, 0.5, 0.92, 0.85, "", "brNDC")
    output.SetLineWidth(0)
    output.SetLineStyle(0)
    output.SetFillStyle(0)
    output.SetBorderSize(0)
    output.SetTextFont(62)
    output.SetNColumns(2)
    
    return output

def MakePlot(FileName,categoriy,PreOrPost,Xaxis, Status, Channel, year,cat):
    MaxRange=200
    ROOT.gStyle.SetFrameLineWidth(3)
    ROOT.gStyle.SetLineWidth(3)
    ROOT.gStyle.SetOptStat(0)
#    ROOT.gStyle.SetErrorX(0.0001);
    RB_=1

    c=ROOT.TCanvas("canvas","",0,0,600,600)
    c.cd()

    file=ROOT.TFile(FileName,"r")

    adapt=ROOT.gROOT.GetColor(12)
    new_idx=ROOT.gROOT.GetListOfColors().GetSize() + 1
#    trans=ROOT.TColor(new_idx, adapt.GetRed(), adapt.GetGreen(),adapt.GetBlue(), "",0.5)

#    categories=["MuTau_DiJet","MuTau_JetBJet"]
#    ncat=

    Data=file.Get(categoriy[0]).Get("data_obs")
    Data1=file.Get(categoriy[1]).Get("data_obs")
    Data2=file.Get(categoriy[2]).Get("data_obs")
    Data.Add(Data1)
    Data.Add(Data2)
    Data.Rebin(RB_)
    
    ## print Data table for HEPDATA EXO-17-015
#    for bin in range(Data.GetNbinsX()):
#
#        xbin= bin+1
#        LowEdge=int(Data.GetBinLowEdge(xbin))
#        endEdge=int(Data.GetBinLowEdge(xbin)+Data.GetBinWidth(xbin))
#        data_val= int(round(file.Get(categoriy).Get("data_obs").GetBinContent(xbin)))
#        bkg_val=file.Get(categoriy).Get("TotalBkg").GetBinContent(xbin)
#        bkg_val_err=file.Get(categoriy).Get("TotalBkg").GetBinError(xbin)
#        Signal_val=file.Get(categoriy.replace('postfit','prefit')).Get('ggH')
#        Signal_val.Scale( 1.391115 * 2)  # CS x BR  1000_400_440  // factor of 2 is added as we consider the full doublet
#        Signal_val_=Signal_val.GetBinContent(xbin)*1.391115 * 2
##        print "[(%d, %d), %d, (%0.1f,    %0.1f),%0.1f],"%(LowEdge,endEdge,data_val,bkg_val,bkg_val_err,Signal_val_)
#
    
    QCD=file.Get(categoriy[0]).Get("QCD")
    QCD1=file.Get(categoriy[1]).Get("QCD")
    QCD2=file.Get(categoriy[2]).Get("QCD")
    QCD.Add(QCD1)
    QCD.Add(QCD2)
    if '_em' in FileName:
        W=file.Get(categoriy[0]).Get("W")
        W1=file.Get(categoriy[1]).Get("W")
        W2=file.Get(categoriy[2]).Get("W")
        W.Add(W1)
        W.Add(W2)
        QCD.Add(W)
#    if 'CR_' in categoriy: QCD=file.Get(categoriy).Get("W")
    QCD.Rebin(RB_)

#    W=file.Get(categoriy).Get("W")
#    W.Rebin(RB_)

    TT=file.Get(categoriy[1]).Get("TT")
    TT1=file.Get(categoriy[0]).Get("TT")
    TT2=file.Get(categoriy[2]).Get("TT")
    if TT1: TT.Add(TT1)
    TT.Add(TT2)
    TT.Rebin(RB_)

#    ZJ=file.Get(categoriy).Get("ZJ")
#    ZJ.Rebin(RB_)
    
    VV=file.Get(categoriy[0]).Get("VV")
    VV1=file.Get(categoriy[1]).Get("VV")
    VV2=file.Get(categoriy[2]).Get("VV")
    VV.Add(VV1)
    VV.Add(VV2)
    VV.Rebin(RB_)

    ZTT=file.Get(categoriy[0]).Get("ZTT")
    ZTT1=file.Get(categoriy[1]).Get("ZTT")
    ZTT2=file.Get(categoriy[2]).Get("ZTT")
    ZTT.Add(ZTT1)
    ZTT.Add(ZTT2)
    ZTT.Rebin(RB_)
    
    
    signame_ggh=''
    signame_xh=''
    if cat=='bin1': signame_ggh='ggH_PTH_0_350'; signame_xh='XH_PTH_0_350';
    elif cat=='bin2': signame_ggh='ggH_PTH_350_450'; signame_xh='XH_PTH_350_450';
    elif cat=='bin3': signame_ggh='ggH_PTH_450_600'; signame_xh='XH_PTH_450_600';
    elif cat=='bin4': signame_ggh='ggH_PTH_GT600'; signame_xh='XH_PTH_GT600';
    


    
#    Signal=file.Get(categoriy.replace('postfit','prefit')).Get('ggH')
#    Signal2=file.Get(categoriy.replace('postfit','prefit')).Get('XH')
    Signal=file.Get(categoriy[0].replace('postfit','prefit')).Get(signame_ggh)
    Signal1=file.Get(categoriy[1].replace('postfit','prefit')).Get(signame_ggh)
    Signal2=file.Get(categoriy[2].replace('postfit','prefit')).Get(signame_ggh)
    Signal.Add(Signal1)
    Signal.Add(Signal2)
    Signal_XH=file.Get(categoriy[0].replace('postfit','prefit')).Get(signame_xh)
    Signal_XH1=file.Get(categoriy[1].replace('postfit','prefit')).Get(signame_xh)
    Signal_XH2=file.Get(categoriy[2].replace('postfit','prefit')).Get(signame_xh)
    Signal_XH.Add(Signal_XH1)
    Signal_XH.Add(Signal_XH2)
    Signal.Add(Signal_XH)
    Signal.Scale( 20)  # CS x BR  1000_400_440  // factor of 2 is added as we consider the full doublet
    Signal.Rebin(RB_)
    #    Signal.SetFillStyle(0.)
#    Signal.SetLineStyle(11)
    Signal.SetLineWidth(3)
    Signal.SetLineColor(4)
    Signal.SetMarkerColor(4)
#    Signal.SetLineStyle(8)

    Signal.SetLineColor(ROOT.TColor.GetColor(108, 226, 354))
    Signal.SetMarkerColor(ROOT.TColor.GetColor(108, 226, 354))
    Signal.SetLineColor(2)
    


#    ##### Garwood Method to assign error bar to bins with zero content https://twiki.cern.ch/twiki/bin/view/CMS/PoissonErrorBars
#    ALLSample=[Data]
#    for sample in ALLSample:
#        for ibin in range(sample.GetXaxis().GetNbins()):
#            if sample.GetBinContent(ibin)==0:
#                #                sample.SetBinErrorUp(ibin, 1.8)
#                sample.SetBinErrorOption(rt.TH1.kPoisson)
##                sample.GetBinError(ibin,1.8)
#                print "sample.GetBinErrorLow( ",ibin," )", sample.GetBinErrorLow(ibin)
#                print "sample.GetBinErrorUp( ",ibin," )", sample.GetBinErrorUp(ibin)


###### chnage binning content
##    ALLSample=[Data,QCD,W,TT,ZJ,VV,ZTT]
##    ALLSample=[Data,QCD,W,TT,VV,ZTT]
#    ALLSample=[Data,QCD,TT,VV,ZTT]
#    for sample in ALLSample:
#        for ibin in range(sample.GetXaxis().GetNbins()):
##            print ibin+1, sample.GetBinWidth(ibin+1)
#
#            sample.SetBinContent(ibin+1,1.0*sample.GetBinContent(ibin+1)/sample.GetBinWidth(ibin+1))
#            sample.SetBinError(ibin+1,1.0*sample.GetBinError(ibin+1)/sample.GetBinWidth(ibin+1))
#
#            if sample==Data and sample.GetBinContent(ibin+1)==0: #https://twiki.cern.ch/twiki/bin/view/CMS/PoissonErrorBars
#                sample.SetBinError(ibin+1,1.0*1.8/sample.GetBinWidth(ibin+1))
#

    

    Data.GetXaxis().SetTitle("")
    Data.GetXaxis().SetTitleSize(0)
    Data.GetXaxis().SetNdivisions(505)
    Data.GetYaxis().SetLabelFont(42)
    Data.GetYaxis().SetLabelOffset(0.01)
    Data.GetYaxis().SetLabelSize(0.06)
    Data.GetYaxis().SetTitleSize(0.075)
    Data.GetYaxis().SetTitleOffset(1.04)
    Data.SetTitle("")
    Data.GetYaxis().SetTitle("Events / GeV")



    QCD.SetFillColor(ROOT.TColor.GetColor(408, 106, 154))
#    W.SetFillColor(ROOT.TColor.GetColor(200, 2, 285))
    TT.SetFillColor(ROOT.TColor.GetColor(208, 376, 124))
#    ZJ.SetFillColor(ROOT.TColor.GetColor(150, 132, 232))
    VV.SetFillColor(ROOT.TColor.GetColor(200, 282, 232))
    ZTT.SetFillColor(ROOT.TColor.GetColor(108, 226, 354))


#Blinding
#    for i in range(Data.GetNbinsX()):
#        if i > 4 : Data.SetBinContent(i+1,0)
#        if i > 4 : Data.SetBinError(i+1,0)


    ######  Add OverFlow Bin
#    QCD.SetBinContent(18,QCD.Integral(18,20))
#    W.SetBinContent(18,W.Integral(18,20))
#    TT.SetBinContent(18,TT.Integral(18,20))
#    ZJ.SetBinContent(18,ZJ.Integral(18,20))
#    VV.SetBinContent(18,VV.Integral(18,20))
#    ZTT.SetBinContent(18,ZTT.Integral(18,20))
#    Data.SetBinContent(18,Data.Integral(18,20))
#    Signal.SetBinContent(18,Signal.Integral(18,20))




    Data.SetMarkerStyle(20)
    Data.SetMarkerSize(1)
    QCD.SetLineColor(ROOT.kBlack)
#    W.SetLineColor(ROOT.kBlack)
    TT.SetLineColor(ROOT.kBlack)
    ZTT.SetLineColor(ROOT.kBlack)
    VV.SetLineColor(ROOT.kBlack)
#    ZJ.SetLineColor(ROOT.kBlack)
    Data.SetLineColor(ROOT.kBlack)
    Data.SetLineWidth(2)

    stack=ROOT.THStack("stack","stack")
    

    stack.Add(VV)
#    stack.Add(ZJ)
    stack.Add(TT)
#    stack.Add(W)
    stack.Add(QCD)
    stack.Add(ZTT)
#    stack.Add(Signal)

    errorBand = QCD.Clone()
#    errorBand.Add(W)
    errorBand.Add(TT)
    errorBand.Add(VV)
#    errorBand.Add(ZJ)
    errorBand.Add(ZTT)
    errorBand.SetMarkerSize(0)
    errorBand.SetFillColor(16)
    errorBand.SetFillStyle(3001)
    errorBand.SetLineWidth(1)

    pad1 = ROOT.TPad("pad1","pad1",0,0.35,1,1)
    
    pad1.Draw()
    pad1.cd()
#    if Status == "LOG" : pad1.SetLogy() ; pad1.SetLogx()
    if Status == "LOG" : pad1.SetLogy()
    
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
    pad1.SetFrameLineWidth(3)
    pad1.SetFrameBorderMode(0)
    pad1.SetFrameBorderSize(10)

    Data.GetXaxis().SetLabelSize(0)
    
    if Status == "LOG" :Data.SetMaximum(Data.GetMaximum()*2000); Data.SetMinimum(0.001)
#    if Status == "LOG" :Data.SetMaximum(999); Data.SetMinimum(0.01)
    if Status=="Normal": Data.SetMaximum(Data.GetMaximum()*3) ;  Data.SetMinimum(0)


#    Data.GetXaxis().SetRangeUser(0,MaxRange)
    
    Data.SetBinErrorOption(rt.TH1.kPoisson)
    Data.Draw("ex0")
    stack.Draw("histsame")
    errorBand.Draw("e2same")
    Data.Draw("ex0same")
    Signal.Draw("histsame")



########################################################
#Adding Extra signal
#    Signal2=Signal.Clone()
#    Signal2.Scale(2.836/1.391)
##    Signal2.SetLineStyle(11)
#    Signal2.SetLineWidth(3)
#    Signal2.SetLineStyle(2)
#    Signal2.SetLineColor(2)
#    Signal2.SetMarkerColor(2)
#    Signal2.Draw("histsame")

    legende=make_legend()
    legende.AddEntry(Data,"Observed","elp")

    legende.AddEntry(Signal,"H#rightarrow#tau#tau (x20)","l")
#    legende.AddEntry(W,"W+jets","f")
#    legende.AddEntry(Signal2,sigLeg2,"l")
    legende.AddEntry(TT,"t#bar{t}","f")
#    legende.AddEntry(ZJ,"ZJ","f")
    legende.AddEntry(QCD,"QCD multijet","f")
    legende.AddEntry(ZTT,"Z#rightarrow#tau#tau ","f")
    legende.AddEntry(VV,"VV","f")
    legende.AddEntry(errorBand,"Total uncertainty","f")

    legende.Draw()

    l1=add_lumi(year)
    l1.Draw("same")
    l2=add_CMS()
    l2.Draw("same")
    l3=add_Preliminary()
    l3.Draw("same")

    pad1.RedrawAxis()

    categ  = ROOT.TPaveText(0.2, 0.45, 0.45, 0.5, "NDC")
    categ.SetBorderSize(   0 )
    categ.SetFillStyle(    0 )
    categ.SetTextAlign(   12 )
    categ.SetTextSize ( 0.06 )
    categ.SetTextColor(    1 )
    categ.SetTextFont (   61 )
    #       if i==1 or i==3:
#    categ.AddText(PreOrPost+" "+Channel+" "+str(year)+" "+cat)
    categ.AddText(PreOrPost+" "+Channel+" "+" "+cat)
    #       else :
    #        categ.AddText("SS")
    categ.Draw()

    c.cd()
    pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
#    if Status == "LOG" : pad2.SetLogx()
#    pad2.GetXaxis().SetRangeUser(200,5000)
    pad2.SetTopMargin(0.05);
    pad2.SetBottomMargin(0.35);
    pad2.SetLeftMargin(0.18);
    pad2.SetRightMargin(0.05);
    pad2.SetTickx(1)
    pad2.SetTicky(1)
    pad2.SetFrameLineWidth(3)
#    pad2.SetGridx()
    pad2.SetGridy()
    pad2.Draw()
    pad2.cd()
    
    h1=errorBand.Clone()
 
    
    h1.SetMinimum(0.1)
    h1.SetMarkerStyle(20)

    h3=Data.Clone()


    h3.Sumw2()
    h1.Sumw2()
    
    
    h1.SetStats(0)
    h3.SetStats(0)
    h1.SetTitle("")
    
    h1.Divide(errorBand)
    #######  set the bin errors to zero befive divinig data to that
    errorBandZeroErr=errorBand.Clone()
    for ibin in range(errorBandZeroErr.GetXaxis().GetNbins()):
        errorBandZeroErr.SetBinError(ibin+1,0)
    #######
    h3.Divide(errorBandZeroErr)

    for jbin in range(h3.GetXaxis().GetNbins()):
        print h3.GetBinContent(jbin+1), " +/- " ,h3.GetBinError(jbin+1)


#    h1.GetXaxis().SetRangeUser(0,5000)
    h1.GetXaxis().SetTitle(Xaxis)
    h1.GetXaxis().SetLabelSize(0.08)
    h1.GetYaxis().SetLabelSize(0.08)
    h1.GetYaxis().SetTitle("Obs./Exp.")
    h1.GetXaxis().SetNdivisions(505)
    h1.GetYaxis().SetNdivisions(5)
    h1.GetXaxis().SetTitleSize(0.15)
    h1.GetYaxis().SetTitleSize(0.15)
    h1.GetYaxis().SetTitleOffset(0.5)
    h1.GetYaxis().SetLabelOffset(0.02)
    h1.GetXaxis().SetTitleOffset(0.9)
    h1.GetXaxis().SetLabelSize(0.11)
    h1.GetYaxis().SetLabelSize(0.11)
    h1.GetXaxis().SetTitleFont(42)
    h1.GetYaxis().SetTitleFont(42)
#    h1.GetXaxis().SetRangeUser(0,MaxRange)
#    h1.GetYaxis().SetRangeUser(0,h1.GetMaximum()*3)

#    h1.SetMaximum(1.99)
#    for i in range(h3.GetNbinsX()):
#        if i > 5 : h3.SetBinContent(i+1,0)


    h1.Draw("e2")
#    h3.Draw("Ex0psame0")
    h3.Draw("E0Expsame")


#    c.cd()
#    pad1.Draw()

#    ROOT.gPad.RedrawAxis()

#    c.Modified()
    h1.GetYaxis().SetRangeUser(.01,1.99)
#    c.Modified()
    c.SaveAs("_Finalplot_"+str(year)+"_"+prefix+categoriy[0]+Status+"_CMB_"+Channel+"_"+cat+".pdf")
    print "Data.Integral()", file.Get(categoriy[0]).Get("data_obs").Integral()





InputRootfile=sys.argv[1]
prefix=sys.argv[2]
TypeRun=sys.argv[3]

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# For channel-based plots
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if 'single' in TypeRun:

    channel=''
    if '_mt' in InputRootfile:
        channel = 'mt'
    if '_et' in InputRootfile:
        channel = 'et'
    if '_tt' in InputRootfile:
        channel = 'tt'
    if '_em' in InputRootfile:
        channel = 'em'

    type=''
    xAxis=''

    if 'signal' in InputRootfile:
        type = 'signal'
        xAxis = 'Signal NN score'
    if '_qcd' in InputRootfile:
        type = 'qcd'
        xAxis = 'QCD NN score'
    if '_ztt' in InputRootfile:
        type = 'ztt'
        xAxis = 'Ztt NN score'


    category='H_{}_{}_1_13TeV'.format(channel,type)
    cat=''

    FileNamesInfo=[
                   [InputRootfile,category+"_{}".format('postfit'),xAxis,"PostFit",channel],
                   [InputRootfile,category+"_{}".format('prefit'),xAxis,"PreFit",channel],
                   ]

    for i in range(0,len(FileNamesInfo)):

        year=0
        if '2016' in InputRootfile: year =2016
        if '2017' in InputRootfile: year =2017
        if '2018' in InputRootfile: year =2018
        if '2020' in InputRootfile: year =2020

        print FileNamesInfo[i][0],FileNamesInfo[i][1],FileNamesInfo[i][3],FileNamesInfo[i][2],"Normal",FileNamesInfo[i][4], year
        MakePlot(FileNamesInfo[i][0],FileNamesInfo[i][1],FileNamesInfo[i][3],FileNamesInfo[i][2],"Normal",FileNamesInfo[i][4], year,cat)


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# For all-based plots
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
elif 'all' in TypeRun:

#    channel=''
#    if '_mt' in InputRootfile:
#        channel = 'mt'
#    if '_et' in InputRootfile:
#        channel = 'et'
#    if '_tt' in InputRootfile:
#        channel = 'tt'
#    if '_em' in InputRootfile:
#        channel = 'em'



    for i in range(1,37):
        category='ch{}'.format(str(i))
        
        year_=(i-1)/12
        chCat=(i-1)%12
        ch_=chCat/3
        cat_=chCat%3
        
        year=0
        if year_==0: year=2016
        elif year_==1: year=2017
        elif year_==2: year=2018
        
        ch=''
        if ch_==0: ch='em'
        elif ch_==1: ch='et'
        elif ch_==2: ch='mt'
        elif ch_==3: ch='tt'
        
        cat=''
        if cat_==0: cat='qcd'
        elif cat_==1: cat='signal'
        elif cat_==2: cat='ztt'



        type=''
        xAxis=''

        if 'signal' in cat:
            type = 'signal'
            xAxis = 'Signal NN score'
        if 'qcd' in cat:
            type = 'qcd'
            xAxis = 'QCD NN score'
        if 'ztt' in cat:
            type = 'ztt'
            xAxis = 'Ztt NN score'


        FileNamesInfo=[
                       [InputRootfile,category+"_{}".format('postfit'),xAxis,"PostFit",ch],
                       [InputRootfile,category+"_{}".format('prefit'),xAxis,"PreFit",ch],
                       ]

        for i in range(0,len(FileNamesInfo)):

            print FileNamesInfo[i][0],FileNamesInfo[i][1],FileNamesInfo[i][3],FileNamesInfo[i][2],"Normal",FileNamesInfo[i][4], year
            MakePlot(FileNamesInfo[i][0],FileNamesInfo[i][1],FileNamesInfo[i][3],FileNamesInfo[i][2],"Normal",FileNamesInfo[i][4], year,cat)



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# For all-based plots
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
elif 'diff' in TypeRun:

#    channel=''
#    if '_mt' in InputRootfile:
#        channel = 'mt'
#    if '_et' in InputRootfile:
#        channel = 'et'
#    if '_tt' in InputRootfile:
#        channel = 'tt'
#    if '_em' in InputRootfile:
#        channel = 'em'
#


#    for i in range(1,49):
    for i in range(1,17):
#    for i in range(1,5):
        category='ch{}'.format(str(i))
        category2='ch{}'.format(str(i+16))
        category3='ch{}'.format(str(i+32))
        
        year_=(i-1)/16
        chCat=(i-1)%16
        ch_=chCat/4
        cat_=chCat%4
        
        year=0
        if year_==0: year=2016
        elif year_==1: year=2017
        elif year_==2: year=2018
        
        ch=''
        if ch_==0: ch='em'
        elif ch_==1: ch='et'
        elif ch_==2: ch='mt'
        elif ch_==3: ch='tt'
        
        cat=''
        if cat_==0: cat='bin1'
        elif cat_==1: cat='bin2'
        elif cat_==2: cat='bin3'
        elif cat_==3: cat='bin4'



        type=''
        xAxis=''

        if 'bin1' in cat:
            type = 'bin1'
            xAxis = 'bin1 NN score'
        if 'bin2' in cat:
            type = 'bin2'
            xAxis = 'bin2 NN score'
        if 'bin3' in cat:
            type = 'bin3'
            xAxis = 'bin3 NN score'
        if 'bin4' in cat:
            type = 'bin4'
            xAxis = 'bin4 NN score'


        FileNamesInfo=[
                       [InputRootfile,[category+"_{}".format('postfit'),category2+"_{}".format('postfit'),category3+"_{}".format('postfit')],xAxis,"PostFit",ch],
                       [InputRootfile,[category+"_{}".format('prefit'), category2+"_{}".format('prefit'), category3+"_{}".format('prefit')] ,xAxis,"PreFit",ch],
                       ]

        for i in range(0,len(FileNamesInfo)):

            print FileNamesInfo[i][0],FileNamesInfo[i][1],FileNamesInfo[i][3],FileNamesInfo[i][2],"Normal",FileNamesInfo[i][4], year
            MakePlot(FileNamesInfo[i][0],FileNamesInfo[i][1],FileNamesInfo[i][3],FileNamesInfo[i][2],"Normal",FileNamesInfo[i][4], year,cat)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

else:
    print 'whihc type run are you looking for ?'











#
#
#shapes *                ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/$PROCESS H_em_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/XH_PTH_0_350$MASS H_em_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/XH_PTH_350_450$MASS H_em_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/XH_PTH_450_600$MASS H_em_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/XH_PTH_GT600$MASS H_em_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/ggH_PTH_0_350$MASS H_em_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/ggH_PTH_350_450$MASS H_em_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/ggH_PTH_450_600$MASS H_em_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch1              ../2016/125/../common/em_2016_NN.root H_em_1_13TeV/ggH_PTH_GT600$MASS H_em_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/$PROCESS H_mt_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/XH_PTH_0_350$MASS H_mt_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/XH_PTH_350_450$MASS H_mt_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/XH_PTH_450_600$MASS H_mt_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/XH_PTH_GT600$MASS H_mt_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/ggH_PTH_0_350$MASS H_mt_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/ggH_PTH_350_450$MASS H_mt_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/ggH_PTH_450_600$MASS H_mt_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch10             ../2016/125/../common/mt_2016_NN.root H_mt_2_13TeV/ggH_PTH_GT600$MASS H_mt_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/$PROCESS H_mt_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/XH_PTH_0_350$MASS H_mt_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/XH_PTH_350_450$MASS H_mt_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/XH_PTH_450_600$MASS H_mt_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/XH_PTH_GT600$MASS H_mt_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/ggH_PTH_0_350$MASS H_mt_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/ggH_PTH_350_450$MASS H_mt_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/ggH_PTH_450_600$MASS H_mt_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch11             ../2016/125/../common/mt_2016_NN.root H_mt_3_13TeV/ggH_PTH_GT600$MASS H_mt_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/$PROCESS H_mt_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/XH_PTH_0_350$MASS H_mt_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/XH_PTH_350_450$MASS H_mt_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/XH_PTH_450_600$MASS H_mt_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/XH_PTH_GT600$MASS H_mt_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/ggH_PTH_0_350$MASS H_mt_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/ggH_PTH_350_450$MASS H_mt_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/ggH_PTH_450_600$MASS H_mt_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch12             ../2016/125/../common/mt_2016_NN.root H_mt_4_13TeV/ggH_PTH_GT600$MASS H_mt_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/$PROCESS H_tt_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/XH_PTH_0_350$MASS H_tt_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/XH_PTH_350_450$MASS H_tt_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/XH_PTH_450_600$MASS H_tt_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/XH_PTH_GT600$MASS H_tt_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/ggH_PTH_0_350$MASS H_tt_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/ggH_PTH_350_450$MASS H_tt_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/ggH_PTH_450_600$MASS H_tt_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch13             ../2016/125/../common/tt_2016_NN.root H_tt_1_13TeV/ggH_PTH_GT600$MASS H_tt_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/$PROCESS H_tt_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/XH_PTH_0_350$MASS H_tt_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/XH_PTH_350_450$MASS H_tt_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/XH_PTH_450_600$MASS H_tt_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/XH_PTH_GT600$MASS H_tt_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/ggH_PTH_0_350$MASS H_tt_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/ggH_PTH_350_450$MASS H_tt_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/ggH_PTH_450_600$MASS H_tt_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch14             ../2016/125/../common/tt_2016_NN.root H_tt_2_13TeV/ggH_PTH_GT600$MASS H_tt_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/$PROCESS H_tt_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/XH_PTH_0_350$MASS H_tt_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/XH_PTH_350_450$MASS H_tt_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/XH_PTH_450_600$MASS H_tt_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/XH_PTH_GT600$MASS H_tt_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/ggH_PTH_0_350$MASS H_tt_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/ggH_PTH_350_450$MASS H_tt_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/ggH_PTH_450_600$MASS H_tt_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch15             ../2016/125/../common/tt_2016_NN.root H_tt_3_13TeV/ggH_PTH_GT600$MASS H_tt_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/$PROCESS H_tt_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/XH_PTH_0_350$MASS H_tt_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/XH_PTH_350_450$MASS H_tt_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/XH_PTH_450_600$MASS H_tt_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/XH_PTH_GT600$MASS H_tt_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/ggH_PTH_0_350$MASS H_tt_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/ggH_PTH_350_450$MASS H_tt_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/ggH_PTH_450_600$MASS H_tt_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch16             ../2016/125/../common/tt_2016_NN.root H_tt_4_13TeV/ggH_PTH_GT600$MASS H_tt_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/$PROCESS H_em_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/XH_PTH_0_350$MASS H_em_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/XH_PTH_350_450$MASS H_em_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/XH_PTH_450_600$MASS H_em_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/XH_PTH_GT600$MASS H_em_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/ggH_PTH_0_350$MASS H_em_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/ggH_PTH_350_450$MASS H_em_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/ggH_PTH_450_600$MASS H_em_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch17             ../2017/125/../common/em_2017_NN.root H_em_1_13TeV/ggH_PTH_GT600$MASS H_em_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/$PROCESS H_em_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/XH_PTH_0_350$MASS H_em_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/XH_PTH_350_450$MASS H_em_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/XH_PTH_450_600$MASS H_em_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/XH_PTH_GT600$MASS H_em_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/ggH_PTH_0_350$MASS H_em_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/ggH_PTH_350_450$MASS H_em_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/ggH_PTH_450_600$MASS H_em_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch18             ../2017/125/../common/em_2017_NN.root H_em_2_13TeV/ggH_PTH_GT600$MASS H_em_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/$PROCESS H_em_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/XH_PTH_0_350$MASS H_em_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/XH_PTH_350_450$MASS H_em_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/XH_PTH_450_600$MASS H_em_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/XH_PTH_GT600$MASS H_em_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/ggH_PTH_0_350$MASS H_em_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/ggH_PTH_350_450$MASS H_em_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/ggH_PTH_450_600$MASS H_em_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch19             ../2017/125/../common/em_2017_NN.root H_em_3_13TeV/ggH_PTH_GT600$MASS H_em_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/$PROCESS H_em_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/XH_PTH_0_350$MASS H_em_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/XH_PTH_350_450$MASS H_em_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/XH_PTH_450_600$MASS H_em_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/XH_PTH_GT600$MASS H_em_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/ggH_PTH_0_350$MASS H_em_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/ggH_PTH_350_450$MASS H_em_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/ggH_PTH_450_600$MASS H_em_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch2              ../2016/125/../common/em_2016_NN.root H_em_2_13TeV/ggH_PTH_GT600$MASS H_em_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/$PROCESS H_em_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/XH_PTH_0_350$MASS H_em_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/XH_PTH_350_450$MASS H_em_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/XH_PTH_450_600$MASS H_em_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/XH_PTH_GT600$MASS H_em_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/ggH_PTH_0_350$MASS H_em_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/ggH_PTH_350_450$MASS H_em_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/ggH_PTH_450_600$MASS H_em_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch20             ../2017/125/../common/em_2017_NN.root H_em_4_13TeV/ggH_PTH_GT600$MASS H_em_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/$PROCESS H_et_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/XH_PTH_0_350$MASS H_et_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/XH_PTH_350_450$MASS H_et_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/XH_PTH_450_600$MASS H_et_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/XH_PTH_GT600$MASS H_et_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/ggH_PTH_0_350$MASS H_et_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/ggH_PTH_350_450$MASS H_et_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/ggH_PTH_450_600$MASS H_et_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch21             ../2017/125/../common/et_2017_NN.root H_et_1_13TeV/ggH_PTH_GT600$MASS H_et_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/$PROCESS H_et_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/XH_PTH_0_350$MASS H_et_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/XH_PTH_350_450$MASS H_et_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/XH_PTH_450_600$MASS H_et_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/XH_PTH_GT600$MASS H_et_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/ggH_PTH_0_350$MASS H_et_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/ggH_PTH_350_450$MASS H_et_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/ggH_PTH_450_600$MASS H_et_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch22             ../2017/125/../common/et_2017_NN.root H_et_2_13TeV/ggH_PTH_GT600$MASS H_et_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/$PROCESS H_et_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/XH_PTH_0_350$MASS H_et_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/XH_PTH_350_450$MASS H_et_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/XH_PTH_450_600$MASS H_et_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/XH_PTH_GT600$MASS H_et_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/ggH_PTH_0_350$MASS H_et_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/ggH_PTH_350_450$MASS H_et_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/ggH_PTH_450_600$MASS H_et_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch23             ../2017/125/../common/et_2017_NN.root H_et_3_13TeV/ggH_PTH_GT600$MASS H_et_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/$PROCESS H_et_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/XH_PTH_0_350$MASS H_et_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/XH_PTH_350_450$MASS H_et_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/XH_PTH_450_600$MASS H_et_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/XH_PTH_GT600$MASS H_et_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/ggH_PTH_0_350$MASS H_et_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/ggH_PTH_350_450$MASS H_et_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/ggH_PTH_450_600$MASS H_et_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch24             ../2017/125/../common/et_2017_NN.root H_et_4_13TeV/ggH_PTH_GT600$MASS H_et_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/$PROCESS H_mt_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/XH_PTH_0_350$MASS H_mt_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/XH_PTH_350_450$MASS H_mt_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/XH_PTH_450_600$MASS H_mt_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/XH_PTH_GT600$MASS H_mt_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/ggH_PTH_0_350$MASS H_mt_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/ggH_PTH_350_450$MASS H_mt_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/ggH_PTH_450_600$MASS H_mt_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch25             ../2017/125/../common/mt_2017_NN.root H_mt_1_13TeV/ggH_PTH_GT600$MASS H_mt_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/$PROCESS H_mt_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/XH_PTH_0_350$MASS H_mt_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/XH_PTH_350_450$MASS H_mt_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/XH_PTH_450_600$MASS H_mt_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/XH_PTH_GT600$MASS H_mt_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/ggH_PTH_0_350$MASS H_mt_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/ggH_PTH_350_450$MASS H_mt_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/ggH_PTH_450_600$MASS H_mt_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch26             ../2017/125/../common/mt_2017_NN.root H_mt_2_13TeV/ggH_PTH_GT600$MASS H_mt_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/$PROCESS H_mt_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/XH_PTH_0_350$MASS H_mt_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/XH_PTH_350_450$MASS H_mt_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/XH_PTH_450_600$MASS H_mt_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/XH_PTH_GT600$MASS H_mt_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/ggH_PTH_0_350$MASS H_mt_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/ggH_PTH_350_450$MASS H_mt_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/ggH_PTH_450_600$MASS H_mt_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch27             ../2017/125/../common/mt_2017_NN.root H_mt_3_13TeV/ggH_PTH_GT600$MASS H_mt_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/$PROCESS H_mt_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/XH_PTH_0_350$MASS H_mt_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/XH_PTH_350_450$MASS H_mt_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/XH_PTH_450_600$MASS H_mt_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/XH_PTH_GT600$MASS H_mt_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/ggH_PTH_0_350$MASS H_mt_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/ggH_PTH_350_450$MASS H_mt_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/ggH_PTH_450_600$MASS H_mt_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch28             ../2017/125/../common/mt_2017_NN.root H_mt_4_13TeV/ggH_PTH_GT600$MASS H_mt_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/$PROCESS H_tt_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/XH_PTH_0_350$MASS H_tt_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/XH_PTH_350_450$MASS H_tt_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/XH_PTH_450_600$MASS H_tt_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/XH_PTH_GT600$MASS H_tt_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/ggH_PTH_0_350$MASS H_tt_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/ggH_PTH_350_450$MASS H_tt_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/ggH_PTH_450_600$MASS H_tt_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch29             ../2017/125/../common/tt_2017_NN.root H_tt_1_13TeV/ggH_PTH_GT600$MASS H_tt_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/$PROCESS H_em_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/XH_PTH_0_350$MASS H_em_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/XH_PTH_350_450$MASS H_em_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/XH_PTH_450_600$MASS H_em_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/XH_PTH_GT600$MASS H_em_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/ggH_PTH_0_350$MASS H_em_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/ggH_PTH_350_450$MASS H_em_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/ggH_PTH_450_600$MASS H_em_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch3              ../2016/125/../common/em_2016_NN.root H_em_3_13TeV/ggH_PTH_GT600$MASS H_em_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/$PROCESS H_tt_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/XH_PTH_0_350$MASS H_tt_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/XH_PTH_350_450$MASS H_tt_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/XH_PTH_450_600$MASS H_tt_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/XH_PTH_GT600$MASS H_tt_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/ggH_PTH_0_350$MASS H_tt_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/ggH_PTH_350_450$MASS H_tt_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/ggH_PTH_450_600$MASS H_tt_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch30             ../2017/125/../common/tt_2017_NN.root H_tt_2_13TeV/ggH_PTH_GT600$MASS H_tt_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/$PROCESS H_tt_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/XH_PTH_0_350$MASS H_tt_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/XH_PTH_350_450$MASS H_tt_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/XH_PTH_450_600$MASS H_tt_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/XH_PTH_GT600$MASS H_tt_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/ggH_PTH_0_350$MASS H_tt_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/ggH_PTH_350_450$MASS H_tt_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/ggH_PTH_450_600$MASS H_tt_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch31             ../2017/125/../common/tt_2017_NN.root H_tt_3_13TeV/ggH_PTH_GT600$MASS H_tt_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/$PROCESS H_tt_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/XH_PTH_0_350$MASS H_tt_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/XH_PTH_350_450$MASS H_tt_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/XH_PTH_450_600$MASS H_tt_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/XH_PTH_GT600$MASS H_tt_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/ggH_PTH_0_350$MASS H_tt_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/ggH_PTH_350_450$MASS H_tt_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/ggH_PTH_450_600$MASS H_tt_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch32             ../2017/125/../common/tt_2017_NN.root H_tt_4_13TeV/ggH_PTH_GT600$MASS H_tt_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/$PROCESS H_em_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/XH_PTH_0_350$MASS H_em_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/XH_PTH_350_450$MASS H_em_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/XH_PTH_450_600$MASS H_em_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/XH_PTH_GT600$MASS H_em_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/ggH_PTH_0_350$MASS H_em_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/ggH_PTH_350_450$MASS H_em_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/ggH_PTH_450_600$MASS H_em_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch33             ../2018/125/../common/em_2018_NN.root H_em_1_13TeV/ggH_PTH_GT600$MASS H_em_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/$PROCESS H_em_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/XH_PTH_0_350$MASS H_em_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/XH_PTH_350_450$MASS H_em_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/XH_PTH_450_600$MASS H_em_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/XH_PTH_GT600$MASS H_em_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/ggH_PTH_0_350$MASS H_em_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/ggH_PTH_350_450$MASS H_em_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/ggH_PTH_450_600$MASS H_em_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch34             ../2018/125/../common/em_2018_NN.root H_em_2_13TeV/ggH_PTH_GT600$MASS H_em_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/$PROCESS H_em_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/XH_PTH_0_350$MASS H_em_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/XH_PTH_350_450$MASS H_em_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/XH_PTH_450_600$MASS H_em_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/XH_PTH_GT600$MASS H_em_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/ggH_PTH_0_350$MASS H_em_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/ggH_PTH_350_450$MASS H_em_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/ggH_PTH_450_600$MASS H_em_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch35             ../2018/125/../common/em_2018_NN.root H_em_3_13TeV/ggH_PTH_GT600$MASS H_em_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/$PROCESS H_em_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/XH_PTH_0_350$MASS H_em_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/XH_PTH_350_450$MASS H_em_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/XH_PTH_450_600$MASS H_em_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/XH_PTH_GT600$MASS H_em_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/ggH_PTH_0_350$MASS H_em_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/ggH_PTH_350_450$MASS H_em_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/ggH_PTH_450_600$MASS H_em_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch36             ../2018/125/../common/em_2018_NN.root H_em_4_13TeV/ggH_PTH_GT600$MASS H_em_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/$PROCESS H_et_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/XH_PTH_0_350$MASS H_et_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/XH_PTH_350_450$MASS H_et_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/XH_PTH_450_600$MASS H_et_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/XH_PTH_GT600$MASS H_et_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/ggH_PTH_0_350$MASS H_et_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/ggH_PTH_350_450$MASS H_et_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/ggH_PTH_450_600$MASS H_et_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch37             ../2018/125/../common/et_2018_NN.root H_et_1_13TeV/ggH_PTH_GT600$MASS H_et_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/$PROCESS H_et_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/XH_PTH_0_350$MASS H_et_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/XH_PTH_350_450$MASS H_et_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/XH_PTH_450_600$MASS H_et_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/XH_PTH_GT600$MASS H_et_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/ggH_PTH_0_350$MASS H_et_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/ggH_PTH_350_450$MASS H_et_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/ggH_PTH_450_600$MASS H_et_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch38             ../2018/125/../common/et_2018_NN.root H_et_2_13TeV/ggH_PTH_GT600$MASS H_et_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/$PROCESS H_et_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/XH_PTH_0_350$MASS H_et_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/XH_PTH_350_450$MASS H_et_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/XH_PTH_450_600$MASS H_et_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/XH_PTH_GT600$MASS H_et_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/ggH_PTH_0_350$MASS H_et_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/ggH_PTH_350_450$MASS H_et_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/ggH_PTH_450_600$MASS H_et_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch39             ../2018/125/../common/et_2018_NN.root H_et_3_13TeV/ggH_PTH_GT600$MASS H_et_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/$PROCESS H_em_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/XH_PTH_0_350$MASS H_em_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/XH_PTH_350_450$MASS H_em_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/XH_PTH_450_600$MASS H_em_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/XH_PTH_GT600$MASS H_em_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/ggH_PTH_0_350$MASS H_em_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/ggH_PTH_350_450$MASS H_em_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/ggH_PTH_450_600$MASS H_em_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch4              ../2016/125/../common/em_2016_NN.root H_em_4_13TeV/ggH_PTH_GT600$MASS H_em_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/$PROCESS H_et_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/XH_PTH_0_350$MASS H_et_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/XH_PTH_350_450$MASS H_et_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/XH_PTH_450_600$MASS H_et_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/XH_PTH_GT600$MASS H_et_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/ggH_PTH_0_350$MASS H_et_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/ggH_PTH_350_450$MASS H_et_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/ggH_PTH_450_600$MASS H_et_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch40             ../2018/125/../common/et_2018_NN.root H_et_4_13TeV/ggH_PTH_GT600$MASS H_et_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/$PROCESS H_mt_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/XH_PTH_0_350$MASS H_mt_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/XH_PTH_350_450$MASS H_mt_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/XH_PTH_450_600$MASS H_mt_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/XH_PTH_GT600$MASS H_mt_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/ggH_PTH_0_350$MASS H_mt_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/ggH_PTH_350_450$MASS H_mt_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/ggH_PTH_450_600$MASS H_mt_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch41             ../2018/125/../common/mt_2018_NN.root H_mt_1_13TeV/ggH_PTH_GT600$MASS H_mt_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/$PROCESS H_mt_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/XH_PTH_0_350$MASS H_mt_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/XH_PTH_350_450$MASS H_mt_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/XH_PTH_450_600$MASS H_mt_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/XH_PTH_GT600$MASS H_mt_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/ggH_PTH_0_350$MASS H_mt_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/ggH_PTH_350_450$MASS H_mt_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/ggH_PTH_450_600$MASS H_mt_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch42             ../2018/125/../common/mt_2018_NN.root H_mt_2_13TeV/ggH_PTH_GT600$MASS H_mt_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/$PROCESS H_mt_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/XH_PTH_0_350$MASS H_mt_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/XH_PTH_350_450$MASS H_mt_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/XH_PTH_450_600$MASS H_mt_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/XH_PTH_GT600$MASS H_mt_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/ggH_PTH_0_350$MASS H_mt_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/ggH_PTH_350_450$MASS H_mt_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/ggH_PTH_450_600$MASS H_mt_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch43             ../2018/125/../common/mt_2018_NN.root H_mt_3_13TeV/ggH_PTH_GT600$MASS H_mt_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/$PROCESS H_mt_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/XH_PTH_0_350$MASS H_mt_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/XH_PTH_350_450$MASS H_mt_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/XH_PTH_450_600$MASS H_mt_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/XH_PTH_GT600$MASS H_mt_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/ggH_PTH_0_350$MASS H_mt_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/ggH_PTH_350_450$MASS H_mt_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/ggH_PTH_450_600$MASS H_mt_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch44             ../2018/125/../common/mt_2018_NN.root H_mt_4_13TeV/ggH_PTH_GT600$MASS H_mt_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/$PROCESS H_tt_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/XH_PTH_0_350$MASS H_tt_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/XH_PTH_350_450$MASS H_tt_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/XH_PTH_450_600$MASS H_tt_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/XH_PTH_GT600$MASS H_tt_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/ggH_PTH_0_350$MASS H_tt_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/ggH_PTH_350_450$MASS H_tt_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/ggH_PTH_450_600$MASS H_tt_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch45             ../2018/125/../common/tt_2018_NN.root H_tt_1_13TeV/ggH_PTH_GT600$MASS H_tt_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/$PROCESS H_tt_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/XH_PTH_0_350$MASS H_tt_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/XH_PTH_350_450$MASS H_tt_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/XH_PTH_450_600$MASS H_tt_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/XH_PTH_GT600$MASS H_tt_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/ggH_PTH_0_350$MASS H_tt_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/ggH_PTH_350_450$MASS H_tt_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/ggH_PTH_450_600$MASS H_tt_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch46             ../2018/125/../common/tt_2018_NN.root H_tt_2_13TeV/ggH_PTH_GT600$MASS H_tt_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/$PROCESS H_tt_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/XH_PTH_0_350$MASS H_tt_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/XH_PTH_350_450$MASS H_tt_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/XH_PTH_450_600$MASS H_tt_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/XH_PTH_GT600$MASS H_tt_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/ggH_PTH_0_350$MASS H_tt_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/ggH_PTH_350_450$MASS H_tt_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/ggH_PTH_450_600$MASS H_tt_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch47             ../2018/125/../common/tt_2018_NN.root H_tt_3_13TeV/ggH_PTH_GT600$MASS H_tt_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/$PROCESS H_tt_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/XH_PTH_0_350$MASS H_tt_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/XH_PTH_350_450$MASS H_tt_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/XH_PTH_450_600$MASS H_tt_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/XH_PTH_GT600$MASS H_tt_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/ggH_PTH_0_350$MASS H_tt_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/ggH_PTH_350_450$MASS H_tt_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/ggH_PTH_450_600$MASS H_tt_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch48             ../2018/125/../common/tt_2018_NN.root H_tt_4_13TeV/ggH_PTH_GT600$MASS H_tt_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/$PROCESS H_et_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/XH_PTH_0_350$MASS H_et_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/XH_PTH_350_450$MASS H_et_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/XH_PTH_450_600$MASS H_et_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/XH_PTH_GT600$MASS H_et_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/ggH_PTH_0_350$MASS H_et_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/ggH_PTH_350_450$MASS H_et_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/ggH_PTH_450_600$MASS H_et_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch5              ../2016/125/../common/et_2016_NN.root H_et_1_13TeV/ggH_PTH_GT600$MASS H_et_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/$PROCESS H_et_2_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/XH_PTH_0_350$MASS H_et_2_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/XH_PTH_350_450$MASS H_et_2_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/XH_PTH_450_600$MASS H_et_2_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/XH_PTH_GT600$MASS H_et_2_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/ggH_PTH_0_350$MASS H_et_2_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/ggH_PTH_350_450$MASS H_et_2_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/ggH_PTH_450_600$MASS H_et_2_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch6              ../2016/125/../common/et_2016_NN.root H_et_2_13TeV/ggH_PTH_GT600$MASS H_et_2_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/$PROCESS H_et_3_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/XH_PTH_0_350$MASS H_et_3_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/XH_PTH_350_450$MASS H_et_3_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/XH_PTH_450_600$MASS H_et_3_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/XH_PTH_GT600$MASS H_et_3_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/ggH_PTH_0_350$MASS H_et_3_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/ggH_PTH_350_450$MASS H_et_3_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/ggH_PTH_450_600$MASS H_et_3_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch7              ../2016/125/../common/et_2016_NN.root H_et_3_13TeV/ggH_PTH_GT600$MASS H_et_3_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/$PROCESS H_et_4_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/XH_PTH_0_350$MASS H_et_4_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/XH_PTH_350_450$MASS H_et_4_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/XH_PTH_450_600$MASS H_et_4_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/XH_PTH_GT600$MASS H_et_4_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/ggH_PTH_0_350$MASS H_et_4_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/ggH_PTH_350_450$MASS H_et_4_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/ggH_PTH_450_600$MASS H_et_4_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch8              ../2016/125/../common/et_2016_NN.root H_et_4_13TeV/ggH_PTH_GT600$MASS H_et_4_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#shapes *                ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/$PROCESS H_mt_1_13TeV/$PROCESS_$SYSTEMATIC
#shapes XH_PTH_0_350     ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/XH_PTH_0_350$MASS H_mt_1_13TeV/XH_PTH_0_350$MASS_$SYSTEMATIC
#shapes XH_PTH_350_450   ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/XH_PTH_350_450$MASS H_mt_1_13TeV/XH_PTH_350_450$MASS_$SYSTEMATIC
#shapes XH_PTH_450_600   ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/XH_PTH_450_600$MASS H_mt_1_13TeV/XH_PTH_450_600$MASS_$SYSTEMATIC
#shapes XH_PTH_GT600     ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/XH_PTH_GT600$MASS H_mt_1_13TeV/XH_PTH_GT600$MASS_$SYSTEMATIC
#shapes ggH_PTH_0_350    ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/ggH_PTH_0_350$MASS H_mt_1_13TeV/ggH_PTH_0_350$MASS_$SYSTEMATIC
#shapes ggH_PTH_350_450  ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/ggH_PTH_350_450$MASS H_mt_1_13TeV/ggH_PTH_350_450$MASS_$SYSTEMATIC
#shapes ggH_PTH_450_600  ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/ggH_PTH_450_600$MASS H_mt_1_13TeV/ggH_PTH_450_600$MASS_$SYSTEMATIC
#shapes ggH_PTH_GT600    ch9              ../2016/125/../common/mt_2016_NN.root H_mt_1_13TeV/ggH_PTH_GT600$MASS H_mt_1_13TeV/ggH_PTH_GT600$MASS_$SYSTEMATIC
#
