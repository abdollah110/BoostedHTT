## \file
 ## \ingroup tutorial_pyroot
 ## \notebook
 ## A Simple Graph Example
 ##
 ## \macro_image
 ## \macro_output
 ## \macro_code
 ##
 ## \author Wim Lavrijsen
 
#from __future__ import print_function
from ROOT import TCanvas, TGraph,TGraphErrors, TFile
from ROOT import gROOT
from math import sin
from array import array
import sys


infile=sys.argv[1]

c1 = TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
c1.SetGrid()

n = 3
m = 1
x, x_ ,dx,dx_= array( 'd' ), array( 'd' ),array( 'd' ), array( 'd' )

## This is for SF v.s. pt
#x_.append(118)
#x.append(40)
#x.append(75)
#x.append(150)
#
#dx_.append(85)
#dx.append(10)
#dx.append(25)
#dx.append(50)

# This is for SF v.s. dR
x_.append(0.45)
x.append(0.3)
x.append(0.575)
x.append(0.725)

dx_.append(0.35)
dx.append(0.2)
dx.append(0.075)
dx.append(0.075)


y_val=0

Years=['2016','2017','2018']
WPs=['V','L','M','T']
#WPs=['V','M','T']
Bins=['bin0','bin1','bin2','bin3']

for year in Years:
    for wp in WPs:
        y, y_ ,dy,dy_= array( 'd' ), array( 'd' ),array( 'd' ), array( 'd' )
        for bin in Bins:
            print '\n\n %%%%%%%%%%%%%% stating {} {} {} '.format(year,wp,bin)
            if bin == 'bin0':
            
                input1=TFile('{}/{}_{}_{}/125/higgsCombineTest.FitDiagnostics.mH125.root'.format(infile,year,wp,bin),'r')
                if not input1: print input1, 'does not exist'; continue
                tr1=input1.Get('limit')
                for i in tr1:
                    if round(i.quantileExpected,2) == 0.5:
                        y_.append(round(i.limit,2))
                        y_val=i.limit
                print y_val
                for i in tr1:
                    if round(i.quantileExpected,2) == 0.16:
#                    if round(i.quantileExpected,2) == 0.84:
                        dy_.append(round(-i.limit+y_val,2))
            else:

                input1=TFile('{}/{}_{}_{}/125/higgsCombineTest.FitDiagnostics.mH125.root'.format(infile, year,wp,bin),'r')
                tr1=input1.Get('limit')
                for i in tr1:
                    if round(i.quantileExpected,2) == 0.5:
                        y.append(round(i.limit,2))
                        y_val=i.limit
                print y_val
                for i in tr1:
                    if round(i.quantileExpected,2) == 0.16:
#                    if round(i.quantileExpected,2) == 0.84:
                        dy.append(round(-i.limit+y_val,2))
        

        gr_tot = TGraphErrors( m, x_, y_ ,dx_,dy_)
        gr_tot.SetLineColor( 2 )
        gr_tot.SetLineWidth( 6 )
        gr_tot.SetLineStyle( 5 )
        gr_tot.SetMarkerColor( 2 )
        gr_tot.SetMarkerStyle( 24 )
        gr_tot.SetTitle( '{}  wp : {}'.format(year,wp) )
#        gr_tot.GetXaxis().SetTitle( '#tau p_{T} [GeV]' )
        gr_tot.GetXaxis().SetTitle( 'dR_lep_lep' )
        gr_tot.GetYaxis().SetTitle( 'Data/MC SF' )
        gr_tot.GetYaxis().SetTitleSize(0.05)
        gr_tot.GetXaxis().SetTitleSize(0.04)
        gr_tot.GetYaxis().SetRangeUser(0,1.5 )
#        gr_tot.GetXaxis().SetRangeUser(0,200 )
        gr_tot.GetXaxis().SetRangeUser(0,1 )
        gr_tot.Draw( 'AeP' )


        gr_bins = TGraphErrors( n, x, y ,dx,dy)
        gr_bins.SetLineColor( 9 )
        gr_bins.SetLineWidth( 2 )
        gr_bins.SetMarkerColor( 9 )
        gr_bins.SetMarkerStyle( 21 )
        gr_bins.Draw( 'Pesame' )

        c1.SaveAs('sf_{}_{}_dR.pdf'.format(year,wp))
