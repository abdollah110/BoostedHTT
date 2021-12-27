from ROOT import *
import sys
input=sys.argv[1]
year=0
if '2016' in input: year =2016
elif '2017' in input: year =2017
elif '2018' in input: year =2018
else: print 'Which year are you looking for\n'
#DeNums='denum_eta'
#Nums=['numVLoose_eta','numLoose_eta','numTight_eta']
DeNums='denum'
Nums=['numVLoose','numLoose','numTight']

for num in Nums:
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
    numHist.Add(numHistW,-1)
    
    denumHist.Add(denumHistvv,-1)
    denumHist.Add(denumHistztt,-1)
    denumHist.Add(denumHisttt,-1)
    denumHist.Add(denumHistW,-1)
    
    
    numHistRB=numHist.Rebin(2)
    denumHistRB=denumHist.Rebin(2)
    numHistRB.Divide(denumHistRB)
    can=TCanvas()
    numHistRB.GetYaxis().SetRangeUser(0,1)
    numHistRB.Draw()
    can.SaveAs('fr_{}_{}_new_pt_qcd.pdf'.format(num,year))
    can.SaveAs('fr_{}_{}_new_pt_qcd.root'.format(num,year))
    OutRoot=TFile('File_fr_{}_{}_new_pt_qcd.root'.format(num,year),'RECREATE')
    numHistRB.Write()
    OutRoot.Close()

