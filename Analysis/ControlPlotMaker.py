
#python Efficiency.py -i Output/trees/FinalFix0p5_emSig_full_full_output.root,Output/trees/Zprime_94X_fix_Full_zprime_fix_gen_output.root,Output/trees/Zprime_94X_bug_Full_zprime_bug_gen_output.root -s test
#python ControlPlotMaker.py -i Output/trees/skim_fixMiniAOD_output.root,Output/trees/skim_fixAOD_output.root,Output/trees/skim_fixMiniAOD_output.root -s newNeutralIsoPtSum

from ROOT import *
import ROOT
from MyPlot import plot
from collections import namedtuple
import array
import numpy
ROOT.gStyle.SetOptStat(0)

GetColor = ROOT.TColor.GetColor
black = ROOT.kBlack

style_map_tuple = namedtuple('style_map_tuple', [
     'line_color', 'marker_style','marker_color','marker_size'
])
style_map = {
    "Buggy": style_map_tuple( 8,  22,8,1.2),
    "AOD_Fixed": style_map_tuple( 2,  24,2,1.2),
    "MiniAOD_Fixed": style_map_tuple(9, 20,9,1.2),
    }






def ApplyStyle(ihist, styles):
    """Apply styling to histogram."""
    ihist.SetLineColor(styles.line_color)
    ihist.SetMarkerStyle(styles.marker_style)
    ihist.SetMarkerColor(styles.marker_color)
    ihist.SetMarkerSize(styles.marker_size)
    return ihist


def createCanvas():
    """Build the TCanvas and split into pads."""
    can = ROOT.TCanvas('can', 'can', 600, 600)
#    can.Divide(2, 1)

    pad1 = can.cd(1)
    pad1.SetLeftMargin(.12)
    pad1.cd()
    pad1.SetPad(0, 0, 1, 1)
    pad1.SetTopMargin(.1)
    pad1.SetBottomMargin(0.12)
#    pad1.SetLogx()
    pad1.SetLogy()
    pad1.SetTickx(1)
    pad1.SetTicky(1)

#    pad2 = can.cd(2)
#    pad2.SetLeftMargin(.12)
#    pad2.SetPad(0, 0, 1, .3)
#    pad2.SetTopMargin(0.06)
#    pad2.SetBottomMargin(0.35)
#    pad2.SetTickx(1)
#    pad2.SetTicky(1)
#
#    can.cd(1)
    return can
    

def fillLegend(bug, aod, miniaod):
    """Fill the legend with appropriate processes."""
    leg = ROOT.TLegend(0.4, 0.7, 0.75, 0.85)
    leg.SetLineColor(0)
    leg.SetFillColor(0)
    leg.SetTextFont(61)
    leg.SetTextFont(42)
    leg.SetTextSize(0.035)

    leg.AddEntry(aod, 'AOD_fixed', 'lep')
    leg.AddEntry(miniaod, 'MiniOAD_fixed', 'lep')
    leg.AddEntry(bug, 'Buggy', 'lep')
    
    return leg
    

#NumHisto='HiggsPt_num'

#rb_ = array.array('d', [0,2,4,6,8,10,30,50,70,90,110,140,170,200])
#rb_ = array.array('d', [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,45,50,60,70,80,90,100,120,140,160,180,200])
#NumHisto='NeutralIsoPtSum'

#rb_ = array.array('d', [0,0.1,0.2,.3,.4,.5,.6,.7,.8,.9,1])

rb_ = array.array('d', [-1,-0.9,-0.8,-.7,-.6,-0.5,-.4,-0.3,-0.2,-0.1,0,.1,.2,.3,.4,.5,.6,.7,.8,.9,1])
NumHisto='boostedTauByIsolationMVArun2v1DBoldDMwLTraw_lead'


def main(args):
        

    can = createCanvas()
    
    InFile=TFile(args.input.split(',')[0],'read')
    numHist=InFile.Get(NumHisto+'NoOverLap')
    numHist_=numHist.Rebin(len(rb_)-1,'numHist',rb_)
    numHist_=ApplyStyle(numHist_,style_map["MiniAOD_Fixed"])
    
    numHist_.SetTitle('')
    numHist_.SetMaximum(numHist_.GetMaximum()*1.2)
#    numHist_.GetYaxis().SetTitle('#tau_{h}#tau_{h} selection efficiency')
    numHist_.GetYaxis().SetTitleSize(.05)
    numHist_.GetYaxis().SetTitleOffset(1.0)
#    numHist_.GetXaxis().SetTitle('Higgs p_{T} [GeV]')
    numHist_.GetXaxis().SetTitle('MVA Isolation raw')
#    numHist_.GetXaxis().SetTitle('Neutral Iso Pt Sum [GeV]')
#    numHist_.GetXaxis().SetTitle('NeutralIsoPtSum')
    numHist_.GetXaxis().SetTitleSize(.05)
    numHist_.GetXaxis().SetTitleOffset(1.0)
    numHist_.Draw()
    
    InFile2=TFile(args.input.split(',')[1],'read')
    numHist2=InFile2.Get(NumHisto+'NoOverLap')
    numHist_2=numHist2.Rebin(len(rb_)-1,'numHist2',rb_)
    numHist_2=ApplyStyle(numHist_2,style_map["AOD_Fixed"])
    numHist_2.Draw('same')


    InFile3=TFile(args.input.split(',')[2],'read')
    numHist3=InFile3.Get(NumHisto)
    numHist_3=numHist3.Rebin(len(rb_)-1,'numHist3',rb_)
    numHist_3=ApplyStyle(numHist_3,style_map["Buggy"])
    numHist_3.Draw('same')

    legend = fillLegend(numHist_3, numHist_2, numHist_)
    legend.Draw()




    can.SaveAs('NeutralIsoPtSum_{}.pdf'.format(args.suff))
    

# if the __name__ is equal to __main__, it implies tha the module is being run standalone by the user, but if it is the same as the name of the module, it means that it is being vcalled by another module
if __name__ == "__main__":
    
    from argparse import ArgumentParser
    parser= ArgumentParser()
    parser.add_argument('--input','-i',required=True,help='provide input file' )
    parser.add_argument('--suff','-s',required=True,help='provide suffix' )
    main(parser.parse_args())

