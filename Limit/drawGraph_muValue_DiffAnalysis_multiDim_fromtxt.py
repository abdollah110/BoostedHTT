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
from ROOT import TCanvas, TGraph,TGraphErrors, TFile,TGraphAsymmErrors
from ROOT import gROOT
from math import sin
from array import array
import sys


prefix=sys.argv[1]

c1 = TCanvas( 'c1', 'A Simple Graph Example', 200, 10, 700, 500 )
c1.SetGrid()

n = 4
m = 4
x, x_ ,dx,dxl= array( 'd' ), array( 'd' ),array( 'd' ), array( 'd' )

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
x.append(175)
x.append(400)
x.append(525)
x.append(800)

dx.append(25)
dx.append(25)
dx.append(25)
dx.append(25)
dxl.append(25)
dxl.append(25)
dxl.append(25)
dxl.append(25)


y_val=0

Years=['2016','2017','2018','em','et','mt','tt','all']
#Years=['2016','2017','2018']
#Years=['em','et','mt','tt']
#Years=['all']
##WPs=['V','M','T']
Bins=['r_H_PTH_0_350','r_H_PTH_350_450','r_H_PTH_450_600','r_H_PTH_GT600']

for year in Years:
#    for wp in WPs:
    y,dy,dyl= array( 'd' ), array( 'd' ), array( 'd' )
    for bin in Bins:
        print '\n\n %%%%%%%%%%%%%% stating {} {} '.format(year,bin)
#        if bin == 'bin0':

        with open('FITALL_multiDim/higgsCombineTest.MultiDimFit.mH125_{}_{}.root_scan.txt'.format(year,bin),'r') as f:
            lines=f.readline()
            print 'here ther are', ' zero is ', lines.split(" ")[0], ' one is ', lines.split(" ")[1], ' two is ' , lines.split(" ")[2],' three is ', lines.split(" ")[3], ' 4 is ', lines.split(" ")[4]
            y.append(float(lines.split(" ")[2]))
            dy.append(abs(float(lines.split(" ")[3])))
            dyl.append(abs(float(lines.split(" ")[4])))
            print 'here ther are', lines.split(" ")[0], y, dy, dyl

#        higgsCombineTest.MultiDimFit.mH125_2018_r_H_PTH_GT600.root_scan.txt
#
#        input1=TFile('FITALL/higgsCombineTest.FitDiagnostics.mH125_{}_{}.root'.format(year,bin),'r')
#        if not input1: print input1, 'does not exist'; continue
#        tr1=input1.Get('limit')
#        for i in tr1:
#            if round(i.quantileExpected,2) == 0.5:
#                y.append(round(i.limit,2))
#                y_val=i.limit
#        print y_val
#        for i in tr1:
#            if round(i.quantileExpected,2) == 0.16:
##                    if round(i.quantileExpected,2) == 0.84:
#                dy.append(abs(round(-i.limit+y_val,2)))
#                print 'err high', round(-i.limit+y_val,2),
#            if round(i.quantileExpected,2) == 0.84:
#                dyl.append(abs(round(-1*(-i.limit+y_val),2)))
#                print 'err low', round(-1*(-i.limit+y_val),2),
#        else:
#
#            input1=TFile('{}/{}_{}_{}/125/higgsCombineTest.FitDiagnostics.mH125.root'.format(infile, year,wp,bin),'r')
#            tr1=input1.Get('limit')
#            for i in tr1:
#                if round(i.quantileExpected,2) == 0.5:
#                    y.append(round(i.limit,2))
#                    y_val=i.limit
#            print y_val
#            for i in tr1:
#                if round(i.quantileExpected,2) == 0.16:
##                    if round(i.quantileExpected,2) == 0.84:
#                    dy.append(round(-i.limit+y_val,2))
    

    gr_tot = TGraphAsymmErrors( m, x, y ,dx,dxl,dy,dyl)
#    gr_tot = TGraphAsymmErrors( x, y ,dx,dxl,dy,dyl)
#    print 'm is ', m
    gr_tot.SetLineColor( 2 )
    gr_tot.SetLineWidth( 6 )
    gr_tot.SetLineStyle( 5 )
    gr_tot.SetMarkerColor( 2 )
    gr_tot.SetMarkerStyle( 24 )
    gr_tot.SetTitle( '{}'.format(year) )
    gr_tot.GetXaxis().SetTitle( 'Higgs p_{T} [GeV]' )
    gr_tot.GetYaxis().SetTitle( '#mu' )
    gr_tot.GetYaxis().SetTitleSize(0.05)
    gr_tot.GetXaxis().SetTitleSize(0.04)
    gr_tot.GetYaxis().SetRangeUser(-5,10 )
    if 'tt' in year: gr_tot.GetYaxis().SetRangeUser(-5,15 )
    if 'all' in year: gr_tot.GetYaxis().SetRangeUser(-2,5 )
#        gr_tot.GetXaxis().SetRangeUser(0,200 )
    gr_tot.GetXaxis().SetRangeUser(0,1000 )
    gr_tot.Draw( 'AeP' )


#    gr_bins = TGraphErrors( n, x, y ,dx,dy)
#    gr_bins.SetLineColor( 9 )
#    gr_bins.SetLineWidth( 2 )
#    gr_bins.SetMarkerColor( 9 )
#    gr_bins.SetMarkerStyle( 21 )
#    gr_bins.Draw( 'Pesame' )

    c1.SaveAs('muValue_multidim_{}_{}.pdf'.format(prefix, year))
