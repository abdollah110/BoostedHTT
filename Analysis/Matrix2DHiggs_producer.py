import ROOT
from ROOT import *
import sys
from glob import glob

#def DrawMatrix(file):
def add_info(info):
    lowX=0.15
    lowY=0.84
    lumi  = ROOT.TPaveText(lowX, lowY+0.06, lowX+0.15, lowY+0.16, "NDC")
    lumi.SetTextFont(61)
    lumi.SetTextSize(0.032)
    lumi.SetBorderSize(   0 )
    lumi.SetFillStyle(    0 )
    lumi.SetTextAlign(   12 )
    lumi.SetTextColor(    1 )
    lumi.AddText(info)
    return lumi


#fileList = [ifile for ifile in glob('Matrix2DHiggs/*') if '.root' in ifile]
fileList = [ifile for ifile in glob('Matrix2DHiggs_New/*') if '.root' in ifile]



for file in fileList:


    year=0
    if '2016' in file:
        year = 2016
    elif '2017' in file:
        year = 2017
    elif '2018' in file:
        year = 2018
    else:
        print 'which year ???'


    if 'em2' in file or 'em' in file:
        channel = 'em'
        channelName='em'
#            treeName = 'emu_tree'
    elif 'me2' in file or    'me' in file:
#                channel = 'me'
        channel = 'me'
        channelName='em'
        treeName = 'mue_tree'
    elif 'mt2' in file or 'mt' in file:
        channel = 'mt'
        channelName='mt'
        treeName = 'mutau_tree'
    elif 'et2' in file  or  'et' in file:
        channel = 'et'
        channelName='et'
#            treeName = 'etau_tree'
    elif 'tt2' in file  or  'tt' in file:
        channel = 'tt'
        channelName='tt'
    else:
        print 'which channel ???'
        
        
    InFile=TFile(file)
#    ggH=InFile.Get(channelName+"_0jet/ggH125_2D")
#    XH=InFile.Get(channelName+"_0jet/XH125_2D")
    ggH=InFile.Get(channelName+"_0jet/ggH125_2D_Higgs")
    XH=InFile.Get(channelName+"_0jet/XH125_2D_Higgs")
#    ggH=InFile.Get(channelName+"_0jet/ggH125_2D_Jet")
#    XH=InFile.Get(channelName+"_0jet/XH125_2D_Jet")

    ggH.Add(XH)
    
    
#    mat=TH2F('mat','mat',5,0,5,5,0,5)
    mat=TH2F('mat','mat',4,0,4,4,0,4)
    row=[]
    col=[]
    row_sum=0
    
    for i in range(0,4):
        col_sum=0
        for j in range(0,4):
            print ggH.GetBinContent(i+1,j+1)
            col_sum +=ggH.GetBinContent(i+1,j+1)
        col.append(col_sum)

    for i in range(0,4):
        row_sum=0
        for j in range(0,4):
            row_sum +=ggH.GetBinContent(j+1,i+1)
        row.append(row_sum)

    for i in range(0,4):
        for j in range(0,4):
#            mat.SetBinContent(i+1,j+1,round(ggH.GetBinContent(i+1,j+1)/col[i],2))
            mat.SetBinContent(i+1,j+1,round(ggH.GetBinContent(i+1,j+1)/row[j],2))

#    AxisName=['[0,300]','[300,400]','[400,550]','[550,800]','[800,2000]']
    AxisName=['[0,350]','[350,450]','[450,600]','[600,2000]']
    for i in range(0,4):
        mat.GetXaxis().SetBinLabel(i+1,AxisName[i])
        mat.GetYaxis().SetBinLabel(i+1,AxisName[i])
    
    mat.GetXaxis().SetTitle('Higgs P_{T;gen} [GeV]')
    mat.GetYaxis().SetTitle('Higgs P_{T;reco} [GeV]')
#    mat.GetXaxis().SetTitle('LeadJet P_{T;gen} [GeV]')
#    mat.GetYaxis().SetTitle('LeadJet P_{T;reco} [GeV]')
    
    
    ROOT.gStyle.SetFrameLineWidth(3)
    ROOT.gStyle.SetLineWidth(3)
    ROOT.gStyle.SetOptStat(0)
    ROOT.gStyle.SetPadLeftMargin(0.15)
#    ROOT.gStyle.SetPadRightMargin(0.4)

    mat.GetXaxis().SetTitleSize(0)
    mat.GetXaxis().SetNdivisions(505)
    mat.GetYaxis().SetLabelFont(42)
    mat.GetYaxis().SetLabelOffset(0.01)
    mat.GetXaxis().SetTitleOffset(1.254)
    mat.GetYaxis().SetLabelSize(0.035)
    mat.GetYaxis().LabelsOption('h')
#    mat.GetXaxis().LabelsOption('v')
    mat.GetYaxis().SetTitleSize(0.035)
    mat.GetXaxis().SetLabelSize(0.035)
    mat.GetXaxis().SetTitleSize(0.035)
    mat.GetYaxis().SetTitleOffset(2.254)
    mat.GetYaxis().SetLabelOffset(.000254)
    mat.SetTitle("")


#    can=TCanvas("canvas","",100,100,500,500)
    can=TCanvas("canvas","",0,0,500,500)
    mat.Draw("boxtext")
    
    l2=add_info('{}_{}, {}'.format(year,channelName,'Row Unity Normalization Response Matrix'))
#    l2=add_info('{}_{}, {}'.format(year,channel,'Column Unity Normalization Response Matrix'))
    l2.Draw("same")
    
#    can.SaveAs('Response_Matrix_Row_{}_{}.pdf'.format(year,channelName))
#    can.SaveAs('Response_Matrix_Column_{}_{}_Higgs.pdf'.format(year,channel))
#    can.SaveAs('Response_Matrix_Column_{}_{}_Jet.pdf'.format(year,channel))
#    can.SaveAs('Response_Matrix_Row_{}_{}_Jet.pdf'.format(year,channel))
    can.SaveAs('Response_Matrix_Row_{}_{}_Higgs.pdf'.format(year,channel))
    

