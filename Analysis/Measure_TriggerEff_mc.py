from ROOT import *

Type_2D=['ht','met']
Type_1D=['SDMass','AK8Pt','PFMET','PFHT']
Year = ['2016','2017','2018']

#TrgEff_MC_mj_2017
#-rw-------  1 abdollah   65138 Mar 25 15:23 DYJetsToLL_Pt-100To250.root
#-rw-------  1 abdollah   81061 Mar 25 15:23 DYJetsToLL_Pt-250To400.root
#-rw-------  1 abdollah   80028 Mar 25 15:23 DYJetsToLL_Pt-400To650.root
#-rw-------  1 abdollah   50151 Mar 25 15:23 DYJetsToLL_Pt-50To100.root
#-rw-------  1 abdollah  104653 Mar 25 15:23 DYJetsToLL_Pt-650ToInf.root

def XS(year):
    if year=='2016': return 35900.
    elif year=='2017': return 41500.
    elif year=='2018': return 59610.
    else: return 1
    
for year in Year:

    list=[]

    inputFile50= TFile('TrgEff_MC_mj_{}/DYJetsToLL_Pt-50To100.root'.format(year),'r')
    inputFile100=TFile('TrgEff_MC_mj_{}/DYJetsToLL_Pt-100To250.root'.format(year),'r')
    inputFile250=TFile('TrgEff_MC_mj_{}/DYJetsToLL_Pt-250To400.root'.format(year),'r')
    inputFile400=TFile('TrgEff_MC_mj_{}/DYJetsToLL_Pt-400To650.root'.format(year),'r')
    inputFile650=TFile('TrgEff_MC_mj_{}/DYJetsToLL_Pt-650ToInf.root'.format(year),'r')
        
    list.append(inputFile50)
    list.append(inputFile100)
    list.append(inputFile250)
    list.append(inputFile400)
    list.append(inputFile650)
 
    evt=[]
    for ls in list:
        print ls.Get('hEvents')
        num= ls.Get('hEvents').GetBinContent(2)
        print year, ls, num
        evt.append(num)
 
    
    for type_2D in Type_2D:

        RBX_=1
        RBY_=1
        if type_2D=='met':RBX_=2 ; RBY_=2
        
        numHist=list[0].Get('{}_trgEff_2D_After'.format(type_2D))
        numHist.Scale(XS(year)/evt[0])
        
        denumHist=list[0].Get('{}_trgEff_2D_Before'.format(type_2D))
        denumHist.Scale(XS(year)/evt[0])
        
        for i in range(1,5):
            print 'i is ', i
            numHist.Add(list[i].Get('{}_trgEff_2D_After'.format(type_2D)),XS(year)/evt[i])
            denumHist.Add(list[i].Get('{}_trgEff_2D_Before'.format(type_2D)),XS(year)/evt[i])
        
        
        numHistRB=numHist.RebinY(RBY_).RebinX(RBX_)
        denumHistRB=denumHist.RebinY(RBY_).RebinX(RBX_)
        #numHistRB=numHist.RebinX(2)
        #denumHistRB=denumHist.RebinY(2)
        #numHistRB.GetXaxis().SetRangeUser(0,1200)
        numHistRB.Divide(denumHistRB)
        can=TCanvas()
        #gStyle.SetPaintTextFormat('g');
        gStyle.SetPaintTextFormat('0.1f ')
        gStyle.SetTextSize(0.01);
        gStyle.SetOptStat(0)
        numHistRB.Draw("textcolz")
        can.SaveAs('{}_trgEff_2D_{}_mc.pdf'.format(type_2D,year))
        outFile=TFile('{}_trgEff_2D_{}_mc.root'.format(type_2D,year),'RECREATE')
        outH=numHistRB.Clone()
        outH.SetName('TrgEfficiency2D')
        outH.Write()
        outFile.Close()


    for type_1D in Type_1D:

#        numHist_1D=inputFile.Get('{}_trgEff_1D_After'.format(type_1D))
#        denumHist_1D=inputFile.Get('{}_trgEff_1D_Before'.format(type_1D))

        
        numHist_1D=list[0].Get('{}_trgEff_1D_After'.format(type_1D))
        numHist_1D.Scale(XS(year)/evt[0])
        
        denumHist_1D=list[0].Get('{}_trgEff_1D_Before'.format(type_1D))
        denumHist_1D.Scale(XS(year)/evt[0])
        
        for i in range(1,5):
            print 'i is ', i
            numHist_1D.Add(list[i].Get('{}_trgEff_1D_After'.format(type_1D)),XS(year)/evt[i])
            denumHist_1D.Add(list[i].Get('{}_trgEff_1D_Before'.format(type_1D)),XS(year)/evt[i])


        
        can2=TCanvas()
        gStyle.SetOptStat(0)
        numHist_1D.Divide(denumHist_1D)
        numHist_1D.GetYaxis().SetRangeUser(0,1)
        numHist_1D.Draw()
        can2.SaveAs('{}_trgEff_1D_{}_mc.pdf'.format(type_1D,year))
#
