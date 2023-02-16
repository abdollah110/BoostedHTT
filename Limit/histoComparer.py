import sys
import ROOT
import os
from ROOT import *

F1= sys.argv[1]
F2= sys.argv[2]

    

file1=ROOT.TFile(F1,"r")
file2=ROOT.TFile(F1,"r")

#NameOfFile=F1.replace('.root','')
#if not os.path.exists(NameOfFile):
#    os.makedirs(NameOfFile)


file1.cd()
dirList = file1.GetListOfKeys()

c=TCanvas()
for dir in dirList:
#    print 'dir name is ======  ', dir.ReadObj().GetName()
    TDR= dir.ReadObj()
    dirName=dir.GetName()
    allhist=TDR.GetListOfKeys()
    for hist in allhist:
        print "hist name ", hist.GetName(), "    hist integral ", hist.ReadObj().Integral()
        print hist.ReadObj().Integral() - file2.Get(dirName).Get(hist.GetName()).Integral()
#        print
#        HistNorm = fileNominal.Get(TDR.GetName()).Get(hist.ReadObj().GetName())
#
#        if 'Up' in hist.GetName(): continue
#        if 'Down' in hist.GetName(): continue
#
##        print '\t\t nominal is ', hist.GetName()
#
#        for sys in systs:
#            HistUp=fileNominal.Get(TDR.GetName()).Get(hist.ReadObj().GetName()+'_'+sys+'Up')
#            HistDown=fileNominal.Get(TDR.GetName()).Get(hist.ReadObj().GetName()+'_'+sys+'Down')
#
#            if not HistUp : continue
#
#            print HistNorm.GetName(), HistNorm.Integral()
#            print HistUp.GetName(), HistUp.Integral()
#            print HistDown.GetName(), HistDown.Integral()
#
#            tname=TDR.GetName()+"_"+HistNorm.GetName()+"_"+sys
#
#
#            HistNorm.SetMaximum(HistNorm.GetMaximum()*2)
#            PlotStyle(HistNorm, 2, 2, 1)
#            PlotStyle(HistUp, 3, 2, 2)
#            PlotStyle(HistDown, 4, 3, 3)
#
#            HistUp.SetTitle("")
#            HistUp.Draw()
#            HistNorm.Draw('same')
#            HistDown.Draw('same')
#
#
#            leg=TLegend(0.4,0.7,0.78,0.9)
#            leg.AddEntry(HistUp,'Up: '+str('%2.2f'%HistUp.Integral()),'l')
#            leg.AddEntry(HistNorm,'Nom: '+str('%2.2f'%HistNorm.Integral()),'l')
#            leg.AddEntry(HistDown,'Down: '+str('%2.2f'%HistDown.Integral()),'l')
#            leg.Draw()
#
#
#            ll = ROOT.TLatex()
#            ll.SetNDC(ROOT.kTRUE)
#            ll.SetTextSize(0.06)
#            ll.SetTextFont(42)
#            ll.DrawLatex(0.15, 0.94, tname)
#
#
#
#
#            nom=HistNorm.Integral()
#            up=HistUp.Integral()
#            down=HistDown.Integral()
#
#            if nom==0 :  print "\n\nnom is zero {} in {} \n\n".format( HistUp.GetName(), tname)
##            if nom!=0 and ( up/nom > 1.1 or up/nom < 0.9 or down/nom > 1.1 or down/nom < 0.9):
#            elif up/nom > 1.1 or up/nom < 0.9 : print 'up/nom= ',up/nom, ' down/nom= ', down/nom
#
#            c.SaveAs("{}/_sysCompare_{}.pdf".format(NameOfFile,tname))
