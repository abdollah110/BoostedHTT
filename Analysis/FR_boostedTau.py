from ROOT import *
import numpy
import sys
import array
input=sys.argv[1]
year=0
if '2016' in input: year =2016
elif '2017' in input: year =2017
elif '2018' in input: year =2018
else: print 'Which year are you looking for\n'
#DeNums='denum_eta'
#Nums=['numVLoose_eta','numLoose_eta','numTight_eta']
DeNums='denum'
Nums=['numVLoose']
#Nums=['numVLoose','numLoose','numTight']

for num in Nums:

    WP=num.replace('num','')
    vv=input.replace('Data','VV')
    ztt=input.replace('Data','ZTT')
    tt=input.replace('Data','TT')
    W=input.replace('Data','W')
            
    inputFile=TFile(input,'r')
    inputFileVV=TFile(vv,'r')
    inputFileZTT=TFile(ztt,'r')
    inputFileTT=TFile(tt,'r')
    inputFileW=TFile(W,'r')
    
    numHist=inputFile.Get(num)
    denumHist=inputFile.Get(DeNums)
    
    
    numHistvv=inputFileVV.Get(num)
    denumHistvv=inputFileVV.Get(DeNums)
    numHistztt=inputFileZTT.Get(num)
    denumHistztt=inputFileZTT.Get(DeNums)
    numHisttt=inputFileTT.Get(num)
    denumHisttt=inputFileTT.Get(DeNums)
    numHistW=inputFileW.Get(num)
    denumHistW=inputFileW.Get(DeNums)


    numHist.Add(numHistvv,-1)
    numHist.Add(numHistztt,-1)
    numHist.Add(numHisttt,-1)
#    numHist.Add(numHistW,-1)
    
    denumHist.Add(denumHistvv,-1)
    denumHist.Add(denumHistztt,-1)
    denumHist.Add(denumHisttt,-1)
#    denumHist.Add(denumHistW,-1)
    
    
    
#    xbins = array.array((0,50,100,200,500))
    xbins = array.array('d', [0,30,40,50,60,70,80,100,125,150,175,200,250,300,350,400,450,500])
    numHistRB=numHist.Rebin(17,'numHistRB',xbins)
    denumHistRB=denumHist.Rebin(17,'denumHistRB',xbins)
    
#    numHistRB=numHist.Rebin(2)
#    denumHistRB=denumHist.Rebin(2)
    numHistRB.Divide(denumHistRB)
    can=TCanvas()
    numHistRB.GetYaxis().SetRangeUser(0,1)
    numHistRB.Draw()
    numHistRB.Fit("pol0","","",200,500)
    X=numHistRB.GetFunction("pol0")
    print X.GetParameter(0)
    numHistRB.GetXaxis().SetTitle("tau p_{T} [GeV]")
    numHistRB.GetYaxis().SetTitle(WP+" tau mis-identification rate")
    numHistRB.SetTitle(str(year)+" "+WP)
#    numHistRB.SetState(0)
    numHistRB.SetStats(0)
    TT=TLine(200,X.GetParameter(0)+2*X.GetParError(0),500,X.GetParameter(0)+7*X.GetParError(0))
    TT.SetLineStyle(2)
    TT.SetLineWidth(5)
    TT.Draw('same')
    TT2=TLine(200,X.GetParameter(0)-2*X.GetParError(0),500,X.GetParameter(0)-7*X.GetParError(0))
    TT2.SetLineStyle(2)
    TT2.SetLineWidth(5)
    TT2.Draw('same')
    can.SaveAs('fr_{}_{}_v7_pt.pdf'.format(num,year))
    can.SaveAs('fr_{}_{}_v7_pt.root'.format(num,year))
    OutRoot=TFile('File_fr_{}_{}_v7_pt.root'.format(num,year),'RECREATE')
    numHistRB.Write("")
    OutRoot.Close()

