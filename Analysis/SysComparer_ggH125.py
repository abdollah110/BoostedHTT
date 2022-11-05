import sys
import ROOT
import os
from ROOT import *

F1= sys.argv[1]

systs=[]
systs += [

#'CMS_scale_met_unclustered2016', 'CMS_prefiring', 'CMS_scale_t_2016','CMS_scale_j_2016', 'CMS_trig_tt2016'
#'CMS_scale_t_1prong_et2016','CMS_scale_t_3prong_et2016',
#'CMS_scale_t_1prong1pizero_et2016',
#'CMS_scale_t_1prong_mt2016','CMS_scale_t_3prong_mt2016',
#'CMS_scale_t_1prong1pizero_mt2016',
#'CMS_scale_t_1prong_tt2016','CMS_scale_t_3prong_tt2016',
'CMS_scale_t_1prong1pizero_tt2016',

#'CMS_scale_t_1prong_et2017','CMS_scale_t_3prong_et2017',
#'CMS_scale_t_1prong1pizero_et2017',
#'CMS_scale_t_1prong_mt2017','CMS_scale_t_3prong_mt2017',
#'CMS_scale_t_1prong1pizero_mt2017',
#'CMS_scale_t_1prong_tt2017','CMS_scale_t_3prong_tt2017',
#'CMS_scale_t_1prong1pizero_tt2017',
#
#'CMS_scale_t_1prong_et2018','CMS_scale_t_3prong_et2018',
#'CMS_scale_t_1prong1pizero_et2018',
#'CMS_scale_t_1prong_mt2018','CMS_scale_t_3prong_mt2018',
#'CMS_scale_t_1prong1pizero_mt2018',
#'CMS_scale_t_1prong_tt2018','CMS_scale_t_3prong_tt2018',
#'CMS_scale_t_1prong1pizero_tt2018',
    ]
        
  
def PlotStyle(Histo,color,width, style):
    Histo.SetLineColor(color)
    Histo.SetLineWidth(width)
    Histo.SetLineStyle(style)
    return Histo
    

fileNominal=ROOT.TFile(F1,"r")
#if not os.path.exists('outPlots_'+F1):
#    os.makedirs('outPlots_'+F1)

NameOfFile=F1.replace('.root','')
if not os.path.exists(NameOfFile):
    os.makedirs(NameOfFile)


fileNominal.cd()
dirList = gDirectory.GetListOfKeys()

c=TCanvas()
for dir in dirList:
    print 'dir name is ======  ', dir.ReadObj().GetName()
    TDR= dir.ReadObj()
    if 'PTH' not in dir.ReadObj().GetName(): continue
    if 'em' in dir.ReadObj().GetName(): continue
    allhist=TDR.GetListOfKeys()
    for hist in allhist:
        HistNorm = fileNominal.Get(TDR.GetName()+'/'+hist.GetName())

        if 'ggH_PTH' not in hist.GetName(): continue
        print 'nominal is ', hist.GetName()

        if 'Up' in hist.GetName(): continue
        if 'Down' in hist.GetName(): continue
        print '\t\t now pass the conditions is ', hist.GetName()

        for sys in systs:
                    
        
            print '--> now is starting {}'.format(sys)
            print '##original histName is {}'.format(TDR.GetName()+'/'+hist.GetName())
            print '##original histName is {}/{}'.format(TDR.GetName(),hist.ReadObj().GetTitle())
#            print '&& now is changed to histName is {}'.format(TDR.GetName()).Get(hist.ReadObj().GetName().replace('125','').replace('_CMS','125_CMS'))
#            HistUp=fileNominal.Get(TDR.GetName()).Get(hist.ReadObj().GetTitle()+'_'+sys+'Up')
#            HistDown=fileNominal.Get(TDR.GetName()).Get(hist.ReadObj().GetTitle()+'_'+sys+'Down')
            HistUp=fileNominal.Get(TDR.GetName()+'/'+hist.GetName()+'_'+sys+'Up')
            HistDown=fileNominal.Get(TDR.GetName()+'/'+hist.GetName()+'_'+sys+'Down')


#            print '\t\t\t\t', hist.ReadObj().GetName().replace('125','').replace('_CMS','125_CMS')+'_'+sys+'Down'
#            print '\t\t\t\t', hist.ReadObj().GetName().replace('125','')+'_'+sys+'Down'
            if not HistUp : continue
            if not HistDown : continue
            
#            print HistNorm.GetName(), HistNorm.Integral()
#            print HistUp.GetName(), HistUp.Integral()
#            print HistDown.GetName(), HistDown.Integral()
            
            tname=(TDR.GetName()+'_CAT_'+hist.GetName()).replace('PTH','').replace('Htt_','')


            HistNorm.SetMaximum(HistNorm.GetMaximum()*2)
            PlotStyle(HistNorm, 2, 2, 1)
            PlotStyle(HistUp, 3, 2, 2)
            PlotStyle(HistDown, 4, 3, 3)

            HistUp.SetTitle("")
            HistUp.Draw()
            HistNorm.Draw('same')
            HistDown.Draw('same')
            
            
            leg=TLegend(0.1,0.7,0.48,0.9)
            leg.AddEntry(HistUp,'Up: '+str('%2.2f'%HistUp.Integral()),'l')
            leg.AddEntry(HistNorm,'Nom: '+str('%2.2f'%HistNorm.Integral()),'l')
            leg.AddEntry(HistDown,'Down: '+str('%2.2f'%HistDown.Integral()),'l')
            leg.Draw()
            
            
            ll = ROOT.TLatex()
            ll.SetNDC(ROOT.kTRUE)
            ll.SetTextSize(0.06)
            ll.SetTextFont(42)
            ll.DrawLatex(0.15, 0.94, tname)
        
        
        
            
            nom=HistNorm.Integral()
            up=HistUp.Integral()
            down=HistDown.Integral()
            
            if nom==0 :  print "\n\nnom is zero {} in {} \n\n".format( HistUp.GetName(), tname)
#            if nom!=0 and ( up/nom > 1.1 or up/nom < 0.9 or down/nom > 1.1 or down/nom < 0.9):
            elif up/nom > 1.1 or up/nom < 0.9 : print 'up/nom= ',up/nom, ' down/nom= ', down/nom

            c.SaveAs("{}/_sysCompare_{}.pdf".format(NameOfFile,tname))
