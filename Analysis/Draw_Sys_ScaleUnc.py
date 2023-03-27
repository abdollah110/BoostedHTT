import os
import ROOT
from ROOT import *
import math


def findMaxBin(ibin,histList):
    maxBinContent=0
    maxBinError=0
    print len(histList)
    for hist in histList:
        binContent=hist.GetBinContent(ibin)
        if binContent>maxBinContent:
            maxBinContent=binContent
            maxBinError=hist.GetBinError(ibin)
    return maxBinContent,maxBinError


def findMinBin(ibin,histList):
    minBinContent=1000000
    minBinError=0
    for hist in histList:
        binContent=hist.GetBinContent(ibin)
        if binContent < minBinContent:
            minBinContent=binContent
            minBinError=hist.GetBinError(ibin)
    return minBinContent,minBinError


from glob import glob
from optparse import OptionParser

parser = OptionParser()
parser.add_option('--path', '-p', action='store',
                  default='root_files/', dest='path',
                  help='path to input file directory'
                  )
#parser.add_option('--output-dir', '-o', action='store',
#                  default='', dest='output_dir',
#                  help='name of output directory after Output/trees'
#                  )
(options, args) = parser.parse_args()



InputRootFiles = [ifile for ifile in glob(options.path+'/*') if '.root' in ifile and 'pdfscale.root' not in ifile]
#InputRootFiles = [ifile for ifile in glob(options.path+'/*')]
print options.path
print "InputRootFiles ", InputRootFiles

for inFile in InputRootFiles:

    
    File=TFile(inFile,'R')
    
    File.Cp(File.GetName().replace('.root','_')+"pdfscale.root")
    
    channel=''
    channelName=''
    year=0
    
    if '2016' in inFile:
        year = 2016
    elif '2017' in inFile:
        year = 2017
    elif '2018' in inFile:
        year = 2018
    elif '2020' in inFile:
        year = 2020
    else:
        print 'which year ???'
    print "the found year is {}".format(year)


    if '_em' in inFile or 'em2' in inFile:
        channelName = 'em'
        channel = 'em'
    elif '_me' in inFile or    'me2' in inFile:
        channelName = 'me'
        channel = 'em'
    elif '_mt' in inFile or 'mt2' in inFile:
        channelName = 'mt'
        channel = 'mt'
    elif '_et' in inFile  or  'et2' in inFile:
        channelName = 'et'
        channel = 'et'
    elif '_tt' in inFile  or  'tt2' in inFile:
        channelName = 'tt'
        channel = 'tt'
    else:
        print 'which channel ???'
    print "the found channel is {}".format(channel)


    lastSys=0
    lowBin=0
    highBin=1
##########################################################################################
# PDF Uncertainty
##########################################################################################
    process=['ZTT','TT']
    for pro in process:
    
        if pro=='ZTT': lastSys= 111
        else:
            if year==2016 : lastSys= 227
            elif year==2017 : lastSys= 972
            elif year==2018 : lastSys= 972
        
        print  '\t\t lastSys  -->  ', lastSys

        categories=['_ztt','_qcd','_signal']
        for cat in categories:
            if 'signal' in cat: lowBin=0.35
            HisMean=File.Get('{}{}/{}'.format(channel,cat,pro))
            print 'histo is ', '{}{}/{}'.format(channel,cat,pro)
            histPdfUp=TH1F("pdfUp"+cat,"pdfUp"+cat,HisMean.GetNbinsX(),lowBin , highBin)
            histPdfDown=TH1F("pdfDown"+cat,"pdfDown"+cat,HisMean.GetNbinsX(),lowBin , highBin)
            for ibin in range(0,HisMean.GetNbinsX()):
            
                sumP=0
                numP=0
                sumN=0
                numN=0
                
#                histPdfUpbin=TH1F("PdfUp"+cat+str(ibin),"pdfUp"+cat+str(ibin),100,-1,1)
#                histPdfDownbin=TH1F("PdfDown"+cat+str(ibin),"pdfDown"+cat+str(ibin),100,-1,1)
            
                meanCental=HisMean.GetBinContent(ibin+1)
                meanError=HisMean.GetBinError(ibin+1)
                for isys in range(9,lastSys):

                    HistSys=File.Get('{}_ztt/{}___{}{}{}'.format(channel,pro,channel,cat,str(isys)))
                    meanSys=HistSys.GetBinContent(ibin+1)



                    if meanSys > meanCental:
                        sumP +=((meanSys-meanCental)*(meanSys-meanCental))
                        numP +=1
#                        histPdfUpbin.Fill((meanSys-meanCental)/meanCental)

                    if meanSys < meanCental:
                        sumN +=((meanCental-meanSys)*(meanCental-meanSys))
                        numN +=1
#                        histPdfDownbin.Fill((meanSys-meanCental)/meanCental)
                        
#                newFile=TFile('RecFile.root','UPDATE')
#                tDirectory= newFile.Get('{}'+cat)
#                tDirectory.cd()
#                tDirectory.WriteObject(histPdfUpbin,'histPdfUp'+cat+str(ibin))
#                tDirectory.WriteObject(histPdfDownbin,'histPdfDown'+cat+str(ibin))
#                newFile.Close()

                print '\t\t\t  numP,numN  ',numP,numN
                MaxBinValue= meanCental+math.sqrt( 1./(numP -1) *sumP  )
#                MaxBinValue= meanCental+math.sqrt(sumP)
                if MaxBinValue > 1.2* meanCental:
                    print 'pdf ++ higher ', ibin
                    if meanCental!=0 :
                        print MaxBinValue/meanCental ; MaxBinValue= 1.2* meanCental
                MinBinValue= meanCental-math.sqrt( 1./(numN -1) *sumN  )
#                MinBinValue= meanCental-math.sqrt( sumN  )
                if MinBinValue < 0.8* meanCental:
                    print 'pdf -- lower ', ibin
                    if meanCental != 0 :
                        print MinBinValue/meanCental ;MinBinValue= 0.8* meanCental
                

                histPdfUp.SetBinContent(ibin+1,MaxBinValue)
                histPdfUp.SetBinError(ibin+1,meanError)
                
                histPdfDown.SetBinContent(ibin+1,MinBinValue)
                histPdfDown.SetBinError(ibin+1,meanError)
                
            newFile=TFile(File.GetName().replace('.root','_')+"pdfscale.root",'UPDATE')
            tDirectory= newFile.Get(channel+cat)
            tDirectory.cd()
            tDirectory.WriteObject(histPdfUp,'{}_pdfUp'.format(pro))
            tDirectory.WriteObject(histPdfDown,'{}_pdfDown'.format(pro))
            newFile.Close()

                    


##########################################################################################
# Scale Uncertainty
##########################################################################################

    
    process=['ZTT','TT']
    for pro in process:
        categories=['_ztt','_qcd','_signal']
        for cat in categories:
            if 'signal' in cat: lowBin=0.35
            HisMean=File.Get('{}{}/{}'.format(channel,cat,pro))
            histScaleUp=TH1F("scaleUp"+cat,"scaleUp"+cat,HisMean.GetNbinsX(),lowBin , highBin)
            histScaleDown=TH1F("scaleDown"+cat,"scaleDown"+cat,HisMean.GetNbinsX(),lowBin , highBin)
            for ibin in range(0,HisMean.GetNbinsX()):
            
                listHistForScale=[]
                for isys in range(0,9):
                        
            #        if isys==5 or isys==7: continue  # these 2 are non-physical related to the (2,0.5) or (0.5,2)
                    if isys==6 or isys==8: continue  # these 2 are non-physical related to the (2,0.5) or (0.5,2)
                    
                    
                    hist=File.Get('{}_ztt/{}___{}{}{}'.format(channel,pro,channel,cat,str(isys)))
                    listHistForScale.append(File.Get('{}_ztt/{}___{}{}{}'.format(channel,pro,channel,cat,str(isys))))
                    
                maxBinContent,maxBinError=findMaxBin(ibin+1,listHistForScale)
                minBinContent,minBinError=findMinBin(ibin+1,listHistForScale)
                histScaleUp.SetBinContent(ibin+1,maxBinContent)
                histScaleUp.SetBinError(ibin+1,maxBinError)
                histScaleDown.SetBinContent(ibin+1,minBinContent)
                histScaleDown.SetBinError(ibin+1,minBinError)

            newFile=TFile(File.GetName().replace('.root','_')+"pdfscale.root",'UPDATE')
            tDirectory= newFile.Get(channel+cat)
            tDirectory.cd()
            tDirectory.WriteObject(histScaleUp,'{}_scaleUp'.format(pro))
            tDirectory.WriteObject(histScaleDown,'{}_scaleDown'.format(pro))
            newFile.Close()
        
    
##########################################################################################
# End
##########################################################################################
        



#            print pro, ibin, ' Up sum in quarture is ', math.sqrt( 1./(numP -1) *sumP  ), '   and mean is ', meanCental
#            print pro, ibin, ' Down sum in quarture is ', math.sqrt(1./(numN -1)* sumN  ), '   and mean is ', meanCental

#
#
#
#    print '========>',inFile[2] , 'numP ', numP,   'sumP= ', sumP,  ' Final Number plus is=', math.sqrt( 1./(numP -1) * sumP  ),  '  unc= ', math.sqrt( 1./(numP -1) * sumP  )/ meanCental
#
#    BinValuPlus=math.sqrt( 1./(numP -1) * sumP  )/ meanCental
#    histo_pdf_vs_mass_high.SetBinContent(inFile[2],1+BinValuPlus)
#    histo_pdf_vs_mass_high.GetXaxis().SetBinLabel(inFile[2],inFile[1])
#
#
#    print  '========>', inFile[2],  'numN ', numN,   'sumN= ', sumN,  ' Final Number minus is=', math.sqrt( 1./(numN -1) * sumN  ),  '  unc= ', math.sqrt( 1./(numN -1) * sumN  )/ meanCental
#
#    BinValuMinus=math.sqrt( 1./(numN -1) * sumN  )/ meanCental
#    histo_pdf_vs_mass_low.SetBinContent(inFile[2],1-BinValuMinus)
    


#DY 2016  111 weights 0 nominal 1-8 the 8 scale weights ; 9 to 110 pdf         <weightgroup combine="gaussian" type="PDF_variation">

#DY 2017  1080 weights 0 nominal 1-8 the 8 scale weights ; 9 to 110 pdf     &lt;weightgroup name="NNPDF31_nnlo_hessian_pdfas" combine="symmhessian+as"&gt; # 306000: Hessian conversion of NNPDF31_nnlo_as_0118_1000, mem=0 central value ; Alphas(MZ)=0.118; mem=1-100 ; PDF eig.; mem=101 ; central value Alphas(MZ)=0.116; mem=102 ; central value Alphas(MZ)=0.120

#DY 2018  1080 weights 0 nominal 1-8 the 8 scale weights ; 9 to 110 pdf     &lt;weightgroup name="NNPDF31_nnlo_hessian_pdfas" combine="symmhessian+as"&gt; # 306000: Hessian conversion of NNPDF31_nnlo_as_0118_1000, mem=0 central value ; Alphas(MZ)=0.118; mem=1-100 ; PDF eig.; mem=101 ; central value Alphas(MZ)=0.116; mem=102 ; central value Alphas(MZ)=0.120


#TT 2016  254  weights 0 nominal 1-8 the 8 scale weights ; 9 to 218+9 pdf     <weightgroup combine="hessian" name="PDF_variation">

#TT 2017  1080 weights 0 nominal 1-8 the 8 scale weights ; 9 to 963+9 pdf     <weightgroup combine="hessian" name="PDF_variation1">

#TT 2018  1080 weights 0 nominal 1-8 the 8 scale weights ; 9 to 963+9 pdf     <weightgroup combine="hessian" name="PDF_variation1">






        
#            newFile=TFile(inFile[0],'RECREATE')


#

#            File.Get('{}___ztt{}'.format(str(isys))=
#
#            HistCentral=File.Get('MuJet_LQMass_MT500_MET100_Iso')
#            HistSys=File.Get('MuJet_LQMass_Scale%s_MT500_MET100_Iso'%str(isys))
#            HistSys_Denum=File.Get('___SysScaleDenumerator_%s'%str(isys))
#            HistSys_Denum0=File.Get('___SysScaleDenumerator_0')
#
#            #        HistCentral.Rebin(10)
#            #        HistSys.Rebin(10)
#
#
#
#            #        meanCental=HistCentral.Integral()
#            #        meanSys=HistSys.Integral()
#            meanCental=HistCentral.Integral()
#            meanSys=HistSys.Integral()/(HistSys_Denum.Integral()*1.0/HistSys_Denum0.Integral())
#
#
#            if meanSys/meanCental > Minimum:
#                largestDeviationUp=meanSys/meanCental
#                Minimum=largestDeviationUp
#
#
#            if meanSys/meanCental < Maximum:
#                largestDeviationDown=meanSys/meanCental
#                Maximum=largestDeviationDown
#
#
#
#        print inFile[2], largestDeviationUp, largestDeviationDown
#
#        histo_scale_vs_mass_high.SetBinContent(inFile[2],largestDeviationUp )
#        histo_scale_vs_mass_low.SetBinContent(inFile[2],largestDeviationDown )
#
#
##For DY process I varied the final observable  distribution by applying an event-per-event qcd scale weight. 6 extra distributions have been made for each process. The envelope for each process is obtained by finding the maximum and minimum of each bin of the final observable distribution from the above 6 uncertainties
#
#
#
######################################################################################
#
#filePDF_vs_Mass.cd()
#
#histo_pdf_vs_mass_high.Write()
#histo_pdf_vs_mass_low.Write()
#histo_scale_vs_mass_high.Write()
#histo_scale_vs_mass_low.Write()
#
#
#
#c=ROOT.TCanvas("canvas","",0,0,600,600)
#c.cd()
#c.SetGridy()
#
#
#
#
##pad1 = ROOT.TPad("pad1","pad1",0,0,1,1)
###pad1.SetLogy()
##pad1.Draw()
##pad1.cd()
##pad1.SetFillColor(0)
##pad1.SetBorderMode(0)
##pad1.SetBorderSize(10)
##pad1.SetTickx(1)
##pad1.SetTicky(1)
##pad1.SetLeftMargin(0.18)
##pad1.SetRightMargin(0.05)
##pad1.SetTopMargin(0.122)
##pad1.SetBottomMargin(0.026)
##pad1.SetFrameFillStyle(0)
##pad1.SetFrameLineStyle(0)
##pad1.SetFrameLineWidth(3)
##pad1.SetFrameBorderMode(0)
##pad1.SetFrameBorderSize(10)
#
#
##    histo_pdf_vs_mass_high=File.Get('MuJet_LQMass_MT500_MET100_Iso')
#
#histo_pdf_vs_mass_high.Draw('pL')
#histo_pdf_vs_mass_low.Draw('pLsame')
#histo_scale_vs_mass_high.Draw('pLsame')
#histo_scale_vs_mass_low.Draw('pLsame')
##histo_pdf_vs_mass_high.Draw('AXIS')
#
#histo_pdf_vs_mass_high.GetXaxis().SetRangeUser(0,8)
#histo_pdf_vs_mass_high.GetYaxis().SetRangeUser(0.8,1.2)
#histo_pdf_vs_mass_high.GetXaxis().SetTitle("M_{LQ} [GeV]")
#histo_pdf_vs_mass_high.GetXaxis().SetNdivisions(505)
#histo_pdf_vs_mass_high.GetYaxis().SetLabelFont(42)
#histo_pdf_vs_mass_high.GetYaxis().SetLabelOffset(0.01)
#histo_pdf_vs_mass_high.GetYaxis().SetLabelSize(0.03)
#histo_pdf_vs_mass_high.GetYaxis().SetTitleSize(0.04)
#histo_pdf_vs_mass_high.GetYaxis().SetTitleOffset(1.2)
#histo_pdf_vs_mass_high.SetTitle("")
#histo_pdf_vs_mass_high.GetYaxis().SetTitle("PDF/QCD scale Uncertainty")
#histo_pdf_vs_mass_high.SetLineColor(38)
#histo_pdf_vs_mass_high.SetLineWidth(3)
#histo_pdf_vs_mass_high.SetMarkerColor(38)
#histo_pdf_vs_mass_high.SetMarkerStyle(20)
#
#
#
#
#histo_pdf_vs_mass_low.SetLineColor(38)
#histo_pdf_vs_mass_low.SetLineWidth(3)
#histo_pdf_vs_mass_low.SetMarkerColor(38)
#histo_pdf_vs_mass_low.SetMarkerStyle(20)
#
#
#histo_scale_vs_mass_high.SetLineColor(8)
#histo_scale_vs_mass_high.SetLineWidth(3)
#histo_scale_vs_mass_high.SetMarkerColor(8)
#histo_scale_vs_mass_high.SetMarkerStyle(21)
#
#
#
#histo_scale_vs_mass_low.SetLineColor(8)
#histo_scale_vs_mass_low.SetLineWidth(3)
#histo_scale_vs_mass_low.SetMarkerColor(8)
#histo_scale_vs_mass_low.SetMarkerStyle(21)
#
#
#
#legende=make_legend()
#legende.AddEntry(histo_pdf_vs_mass_low,"PDF uncertainty","lp")
#legende.AddEntry(histo_scale_vs_mass_high,"QCD scale uncertainty","lp")
#legende.Draw()
#
#
#
##categ  = ROOT.TPaveText(0.2, 0.3+0.013, 0.39, 0.4+0.1, "NDC")
##categ.SetBorderSize(   0 )
##categ.SetFillStyle(    0 )
##categ.SetTextAlign(   12 )
##categ.SetTextSize ( 0.05 )
##categ.SetTextColor(    1 )
##categ.AddText('PDF')
##categ.Draw()
#
#
#l2=add_CMS()
#l2.Draw("same")
#l3=add_Preliminary()
#l3.Draw("same")
#
#
#c.RedrawAxis('same')
#
#
#
#c.SaveAs('PDF_Uncertaint_vs_Mass.pdf')
##
##    c.cd()
##    pad2 = ROOT.TPad("pad2","pad2",0,0,1,0.35);
##    pad2.SetTopMargin(0.05);
##    pad2.SetBottomMargin(0.3);
##    pad2.SetLeftMargin(0.18);
##    pad2.SetRightMargin(0.05);
##    #pad2.SetTickx(1)
##    #pad2.SetTicky(1)
##    pad2.SetFrameLineWidth(3)
##    pad2.SetGridx()
##    pad2.SetGridy()
##    pad2.Draw()
##    pad2.cd()
#
#
#
#
#
#
#
#
#filePDF_vs_Mass.Close()







#DY 2016
#   <weightgroup combine="gaussian" type="PDF_variation">
#      <weight id="2001"> pdfset=292201 </weight>
#      <weight id="2002"> pdfset=292202 </weight>
#      <weight id="2003"> pdfset=292203 </weight>
#      <weight id="2004"> pdfset=292204 </weight>
#      <weight id="2005"> pdfset=292205 </weight>
#      <weight id="2006"> pdfset=292206 </weight>
#      <weight id="2007"> pdfset=292207 </weight>
#      <weight id="2008"> pdfset=292208 </weight>
#      <weight id="2009"> pdfset=292209 </weight>
#      <weight id="2010"> pdfset=292210 </weight>
#      <weight id="2011"> pdfset=292211 </weight>
#      <weight id="2012"> pdfset=292212 </weight>
#      <weight id="2013"> pdfset=292213 </weight>
#      <weight id="2014"> pdfset=292214 </weight>
#      <weight id="2015"> pdfset=292215 </weight>
#      <weight id="2016"> pdfset=292216 </weight>
#      <weight id="2017"> pdfset=292217 </weight>
#      <weight id="2018"> pdfset=292218 </weight>
#      <weight id="2019"> pdfset=292219 </weight>
#      <weight id="2020"> pdfset=292220 </weight>
#      <weight id="2021"> pdfset=292221 </weight>
#      <weight id="2022"> pdfset=292222 </weight>
#      <weight id="2023"> pdfset=292223 </weight>
#      <weight id="2024"> pdfset=292224 </weight>
#      <weight id="2025"> pdfset=292225 </weight>
#      <weight id="2026"> pdfset=292226 </weight>
#      <weight id="2027"> pdfset=292227 </weight>
#      <weight id="2028"> pdfset=292228 </weight>
#      <weight id="2029"> pdfset=292229 </weight>
#      <weight id="2030"> pdfset=292230 </weight>
#      <weight id="2031"> pdfset=292231 </weight>
#      <weight id="2032"> pdfset=292232 </weight>
#      <weight id="2033"> pdfset=292233 </weight>
#      <weight id="2034"> pdfset=292234 </weight>
#      <weight id="2035"> pdfset=292235 </weight>
#      <weight id="2036"> pdfset=292236 </weight>
#      <weight id="2037"> pdfset=292237 </weight>
#      <weight id="2038"> pdfset=292238 </weight>
#      <weight id="2039"> pdfset=292239 </weight>
#      <weight id="2040"> pdfset=292240 </weight>
#      <weight id="2041"> pdfset=292241 </weight>
#      <weight id="2042"> pdfset=292242 </weight>
#      <weight id="2043"> pdfset=292243 </weight>
#      <weight id="2044"> pdfset=292244 </weight>
#      <weight id="2045"> pdfset=292245 </weight>
#      <weight id="2046"> pdfset=292246 </weight>
#      <weight id="2047"> pdfset=292247 </weight>
#      <weight id="2048"> pdfset=292248 </weight>
#      <weight id="2049"> pdfset=292249 </weight>
#      <weight id="2050"> pdfset=292250 </weight>
#      <weight id="2051"> pdfset=292251 </weight>
#      <weight id="2052"> pdfset=292252 </weight>
#      <weight id="2053"> pdfset=292253 </weight>
#      <weight id="2054"> pdfset=292254 </weight>
#      <weight id="2055"> pdfset=292255 </weight>
#      <weight id="2056"> pdfset=292256 </weight>
#      <weight id="2057"> pdfset=292257 </weight>
#      <weight id="2058"> pdfset=292258 </weight>
#      <weight id="2059"> pdfset=292259 </weight>
#      <weight id="2060"> pdfset=292260 </weight>
#      <weight id="2061"> pdfset=292261 </weight>
#      <weight id="2062"> pdfset=292262 </weight>
#      <weight id="2063"> pdfset=292263 </weight>
#      <weight id="2064"> pdfset=292264 </weight>
#      <weight id="2065"> pdfset=292265 </weight>
#      <weight id="2066"> pdfset=292266 </weight>
#      <weight id="2067"> pdfset=292267 </weight>
#      <weight id="2068"> pdfset=292268 </weight>
#      <weight id="2069"> pdfset=292269 </weight>
#      <weight id="2070"> pdfset=292270 </weight>
#      <weight id="2071"> pdfset=292271 </weight>
#      <weight id="2072"> pdfset=292272 </weight>
#      <weight id="2073"> pdfset=292273 </weight>
#      <weight id="2074"> pdfset=292274 </weight>
#      <weight id="2075"> pdfset=292275 </weight>
#      <weight id="2076"> pdfset=292276 </weight>
#      <weight id="2077"> pdfset=292277 </weight>
#      <weight id="2078"> pdfset=292278 </weight>
#      <weight id="2079"> pdfset=292279 </weight>
#      <weight id="2080"> pdfset=292280 </weight>
#      <weight id="2081"> pdfset=292281 </weight>
#      <weight id="2082"> pdfset=292282 </weight>
#      <weight id="2083"> pdfset=292283 </weight>
#      <weight id="2084"> pdfset=292284 </weight>
#      <weight id="2085"> pdfset=292285 </weight>
#      <weight id="2086"> pdfset=292286 </weight>
#      <weight id="2087"> pdfset=292287 </weight>
#      <weight id="2088"> pdfset=292288 </weight>
#      <weight id="2089"> pdfset=292289 </weight>
#      <weight id="2090"> pdfset=292290 </weight>
#      <weight id="2091"> pdfset=292291 </weight>
#      <weight id="2092"> pdfset=292292 </weight>
#      <weight id="2093"> pdfset=292293 </weight>
#      <weight id="2094"> pdfset=292294 </weight>
#      <weight id="2095"> pdfset=292295 </weight>
#      <weight id="2096"> pdfset=292296 </weight>
#      <weight id="2097"> pdfset=292297 </weight>
#      <weight id="2098"> pdfset=292298 </weight>
#      <weight id="2099"> pdfset=292299 </weight>
#      <weight id="2100"> pdfset=292300 </weight>
#      <weight id="2101"> pdfset=292301 </weight>
#      <weight id="2102"> pdfset=292302 </weight>






#2017 DY
#&lt;weight id="1010" MUR="1.0" MUF="1.0" PDF="306000" &gt;  &lt;/weight&gt;
#&lt;weight id="1011" MUR="1.0" MUF="1.0" PDF="306001" &gt; PDF=306000 MemberID=1 &lt;/weight&gt;
#&lt;weight id="1012" MUR="1.0" MUF="1.0" PDF="306002" &gt; PDF=306000 MemberID=2 &lt;/weight&gt;
#&lt;weight id="1013" MUR="1.0" MUF="1.0" PDF="306003" &gt; PDF=306000 MemberID=3 &lt;/weight&gt;
#&lt;weight id="1014" MUR="1.0" MUF="1.0" PDF="306004" &gt; PDF=306000 MemberID=4 &lt;/weight&gt;
#&lt;weight id="1015" MUR="1.0" MUF="1.0" PDF="306005" &gt; PDF=306000 MemberID=5 &lt;/weight&gt;
#&lt;weight id="1016" MUR="1.0" MUF="1.0" PDF="306006" &gt; PDF=306000 MemberID=6 &lt;/weight&gt;
#&lt;weight id="1017" MUR="1.0" MUF="1.0" PDF="306007" &gt; PDF=306000 MemberID=7 &lt;/weight&gt;
#&lt;weight id="1018" MUR="1.0" MUF="1.0" PDF="306008" &gt; PDF=306000 MemberID=8 &lt;/weight&gt;
#&lt;weight id="1019" MUR="1.0" MUF="1.0" PDF="306009" &gt; PDF=306000 MemberID=9 &lt;/weight&gt;
#&lt;weight id="1020" MUR="1.0" MUF="1.0" PDF="306010" &gt; PDF=306000 MemberID=10 &lt;/weight&gt;
#&lt;weight id="1021" MUR="1.0" MUF="1.0" PDF="306011" &gt; PDF=306000 MemberID=11 &lt;/weight&gt;
#&lt;weight id="1022" MUR="1.0" MUF="1.0" PDF="306012" &gt; PDF=306000 MemberID=12 &lt;/weight&gt;
#&lt;weight id="1023" MUR="1.0" MUF="1.0" PDF="306013" &gt; PDF=306000 MemberID=13 &lt;/weight&gt;
#&lt;weight id="1024" MUR="1.0" MUF="1.0" PDF="306014" &gt; PDF=306000 MemberID=14 &lt;/weight&gt;
#&lt;weight id="1025" MUR="1.0" MUF="1.0" PDF="306015" &gt; PDF=306000 MemberID=15 &lt;/weight&gt;
#&lt;weight id="1026" MUR="1.0" MUF="1.0" PDF="306016" &gt; PDF=306000 MemberID=16 &lt;/weight&gt;
#&lt;weight id="1027" MUR="1.0" MUF="1.0" PDF="306017" &gt; PDF=306000 MemberID=17 &lt;/weight&gt;
#&lt;weight id="1028" MUR="1.0" MUF="1.0" PDF="306018" &gt; PDF=306000 MemberID=18 &lt;/weight&gt;
#&lt;weight id="1029" MUR="1.0" MUF="1.0" PDF="306019" &gt; PDF=306000 MemberID=19 &lt;/weight&gt;
#&lt;weight id="1030" MUR="1.0" MUF="1.0" PDF="306020" &gt; PDF=306000 MemberID=20 &lt;/weight&gt;
#&lt;weight id="1031" MUR="1.0" MUF="1.0" PDF="306021" &gt; PDF=306000 MemberID=21 &lt;/weight&gt;
#&lt;weight id="1032" MUR="1.0" MUF="1.0" PDF="306022" &gt; PDF=306000 MemberID=22 &lt;/weight&gt;
#&lt;weight id="1033" MUR="1.0" MUF="1.0" PDF="306023" &gt; PDF=306000 MemberID=23 &lt;/weight&gt;
#&lt;weight id="1034" MUR="1.0" MUF="1.0" PDF="306024" &gt; PDF=306000 MemberID=24 &lt;/weight&gt;
#&lt;weight id="1035" MUR="1.0" MUF="1.0" PDF="306025" &gt; PDF=306000 MemberID=25 &lt;/weight&gt;
#&lt;weight id="1036" MUR="1.0" MUF="1.0" PDF="306026" &gt; PDF=306000 MemberID=26 &lt;/weight&gt;
#&lt;weight id="1037" MUR="1.0" MUF="1.0" PDF="306027" &gt; PDF=306000 MemberID=27 &lt;/weight&gt;
#&lt;weight id="1038" MUR="1.0" MUF="1.0" PDF="306028" &gt; PDF=306000 MemberID=28 &lt;/weight&gt;
#&lt;weight id="1039" MUR="1.0" MUF="1.0" PDF="306029" &gt; PDF=306000 MemberID=29 &lt;/weight&gt;
#&lt;weight id="1040" MUR="1.0" MUF="1.0" PDF="306030" &gt; PDF=306000 MemberID=30 &lt;/weight&gt;
#&lt;weight id="1041" MUR="1.0" MUF="1.0" PDF="306031" &gt; PDF=306000 MemberID=31 &lt;/weight&gt;
#&lt;weight id="1042" MUR="1.0" MUF="1.0" PDF="306032" &gt; PDF=306000 MemberID=32 &lt;/weight&gt;
#&lt;weight id="1043" MUR="1.0" MUF="1.0" PDF="306033" &gt; PDF=306000 MemberID=33 &lt;/weight&gt;
#&lt;weight id="1044" MUR="1.0" MUF="1.0" PDF="306034" &gt; PDF=306000 MemberID=34 &lt;/weight&gt;
#&lt;weight id="1045" MUR="1.0" MUF="1.0" PDF="306035" &gt; PDF=306000 MemberID=35 &lt;/weight&gt;
#&lt;weight id="1046" MUR="1.0" MUF="1.0" PDF="306036" &gt; PDF=306000 MemberID=36 &lt;/weight&gt;
#&lt;weight id="1047" MUR="1.0" MUF="1.0" PDF="306037" &gt; PDF=306000 MemberID=37 &lt;/weight&gt;
#&lt;weight id="1048" MUR="1.0" MUF="1.0" PDF="306038" &gt; PDF=306000 MemberID=38 &lt;/weight&gt;
#&lt;weight id="1049" MUR="1.0" MUF="1.0" PDF="306039" &gt; PDF=306000 MemberID=39 &lt;/weight&gt;
#&lt;weight id="1050" MUR="1.0" MUF="1.0" PDF="306040" &gt; PDF=306000 MemberID=40 &lt;/weight&gt;
#&lt;weight id="1051" MUR="1.0" MUF="1.0" PDF="306041" &gt; PDF=306000 MemberID=41 &lt;/weight&gt;
#&lt;weight id="1052" MUR="1.0" MUF="1.0" PDF="306042" &gt; PDF=306000 MemberID=42 &lt;/weight&gt;
#&lt;weight id="1053" MUR="1.0" MUF="1.0" PDF="306043" &gt; PDF=306000 MemberID=43 &lt;/weight&gt;
#&lt;weight id="1054" MUR="1.0" MUF="1.0" PDF="306044" &gt; PDF=306000 MemberID=44 &lt;/weight&gt;
#&lt;weight id="1055" MUR="1.0" MUF="1.0" PDF="306045" &gt; PDF=306000 MemberID=45 &lt;/weight&gt;
#&lt;weight id="1056" MUR="1.0" MUF="1.0" PDF="306046" &gt; PDF=306000 MemberID=46 &lt;/weight&gt;
#&lt;weight id="1057" MUR="1.0" MUF="1.0" PDF="306047" &gt; PDF=306000 MemberID=47 &lt;/weight&gt;
#&lt;weight id="1058" MUR="1.0" MUF="1.0" PDF="306048" &gt; PDF=306000 MemberID=48 &lt;/weight&gt;
#&lt;weight id="1059" MUR="1.0" MUF="1.0" PDF="306049" &gt; PDF=306000 MemberID=49 &lt;/weight&gt;
#&lt;weight id="1060" MUR="1.0" MUF="1.0" PDF="306050" &gt; PDF=306000 MemberID=50 &lt;/weight&gt;
#&lt;weight id="1061" MUR="1.0" MUF="1.0" PDF="306051" &gt; PDF=306000 MemberID=51 &lt;/weight&gt;
#&lt;weight id="1062" MUR="1.0" MUF="1.0" PDF="306052" &gt; PDF=306000 MemberID=52 &lt;/weight&gt;
#&lt;weight id="1063" MUR="1.0" MUF="1.0" PDF="306053" &gt; PDF=306000 MemberID=53 &lt;/weight&gt;
#&lt;weight id="1064" MUR="1.0" MUF="1.0" PDF="306054" &gt; PDF=306000 MemberID=54 &lt;/weight&gt;
#&lt;weight id="1065" MUR="1.0" MUF="1.0" PDF="306055" &gt; PDF=306000 MemberID=55 &lt;/weight&gt;
#&lt;weight id="1066" MUR="1.0" MUF="1.0" PDF="306056" &gt; PDF=306000 MemberID=56 &lt;/weight&gt;
#&lt;weight id="1067" MUR="1.0" MUF="1.0" PDF="306057" &gt; PDF=306000 MemberID=57 &lt;/weight&gt;
#&lt;weight id="1068" MUR="1.0" MUF="1.0" PDF="306058" &gt; PDF=306000 MemberID=58 &lt;/weight&gt;
#&lt;weight id="1069" MUR="1.0" MUF="1.0" PDF="306059" &gt; PDF=306000 MemberID=59 &lt;/weight&gt;
#&lt;weight id="1070" MUR="1.0" MUF="1.0" PDF="306060" &gt; PDF=306000 MemberID=60 &lt;/weight&gt;
#&lt;weight id="1071" MUR="1.0" MUF="1.0" PDF="306061" &gt; PDF=306000 MemberID=61 &lt;/weight&gt;
#&lt;weight id="1072" MUR="1.0" MUF="1.0" PDF="306062" &gt; PDF=306000 MemberID=62 &lt;/weight&gt;
#&lt;weight id="1073" MUR="1.0" MUF="1.0" PDF="306063" &gt; PDF=306000 MemberID=63 &lt;/weight&gt;
#&lt;weight id="1074" MUR="1.0" MUF="1.0" PDF="306064" &gt; PDF=306000 MemberID=64 &lt;/weight&gt;
#&lt;weight id="1075" MUR="1.0" MUF="1.0" PDF="306065" &gt; PDF=306000 MemberID=65 &lt;/weight&gt;
#&lt;weight id="1076" MUR="1.0" MUF="1.0" PDF="306066" &gt; PDF=306000 MemberID=66 &lt;/weight&gt;
#&lt;weight id="1077" MUR="1.0" MUF="1.0" PDF="306067" &gt; PDF=306000 MemberID=67 &lt;/weight&gt;
#&lt;weight id="1078" MUR="1.0" MUF="1.0" PDF="306068" &gt; PDF=306000 MemberID=68 &lt;/weight&gt;
#&lt;weight id="1079" MUR="1.0" MUF="1.0" PDF="306069" &gt; PDF=306000 MemberID=69 &lt;/weight&gt;
#&lt;weight id="1080" MUR="1.0" MUF="1.0" PDF="306070" &gt; PDF=306000 MemberID=70 &lt;/weight&gt;
#&lt;weight id="1081" MUR="1.0" MUF="1.0" PDF="306071" &gt; PDF=306000 MemberID=71 &lt;/weight&gt;
#&lt;weight id="1082" MUR="1.0" MUF="1.0" PDF="306072" &gt; PDF=306000 MemberID=72 &lt;/weight&gt;
#&lt;weight id="1083" MUR="1.0" MUF="1.0" PDF="306073" &gt; PDF=306000 MemberID=73 &lt;/weight&gt;
#&lt;weight id="1084" MUR="1.0" MUF="1.0" PDF="306074" &gt; PDF=306000 MemberID=74 &lt;/weight&gt;
#&lt;weight id="1085" MUR="1.0" MUF="1.0" PDF="306075" &gt; PDF=306000 MemberID=75 &lt;/weight&gt;
#&lt;weight id="1086" MUR="1.0" MUF="1.0" PDF="306076" &gt; PDF=306000 MemberID=76 &lt;/weight&gt;
#&lt;weight id="1087" MUR="1.0" MUF="1.0" PDF="306077" &gt; PDF=306000 MemberID=77 &lt;/weight&gt;
#&lt;weight id="1088" MUR="1.0" MUF="1.0" PDF="306078" &gt; PDF=306000 MemberID=78 &lt;/weight&gt;
#&lt;weight id="1089" MUR="1.0" MUF="1.0" PDF="306079" &gt; PDF=306000 MemberID=79 &lt;/weight&gt;
#&lt;weight id="1090" MUR="1.0" MUF="1.0" PDF="306080" &gt; PDF=306000 MemberID=80 &lt;/weight&gt;
#&lt;weight id="1091" MUR="1.0" MUF="1.0" PDF="306081" &gt; PDF=306000 MemberID=81 &lt;/weight&gt;
#&lt;weight id="1092" MUR="1.0" MUF="1.0" PDF="306082" &gt; PDF=306000 MemberID=82 &lt;/weight&gt;
#&lt;weight id="1093" MUR="1.0" MUF="1.0" PDF="306083" &gt; PDF=306000 MemberID=83 &lt;/weight&gt;
#&lt;weight id="1094" MUR="1.0" MUF="1.0" PDF="306084" &gt; PDF=306000 MemberID=84 &lt;/weight&gt;
#&lt;weight id="1095" MUR="1.0" MUF="1.0" PDF="306085" &gt; PDF=306000 MemberID=85 &lt;/weight&gt;
#&lt;weight id="1096" MUR="1.0" MUF="1.0" PDF="306086" &gt; PDF=306000 MemberID=86 &lt;/weight&gt;
#&lt;weight id="1097" MUR="1.0" MUF="1.0" PDF="306087" &gt; PDF=306000 MemberID=87 &lt;/weight&gt;
#&lt;weight id="1098" MUR="1.0" MUF="1.0" PDF="306088" &gt; PDF=306000 MemberID=88 &lt;/weight&gt;
#&lt;weight id="1099" MUR="1.0" MUF="1.0" PDF="306089" &gt; PDF=306000 MemberID=89 &lt;/weight&gt;
#&lt;weight id="1100" MUR="1.0" MUF="1.0" PDF="306090" &gt; PDF=306000 MemberID=90 &lt;/weight&gt;
#&lt;weight id="1101" MUR="1.0" MUF="1.0" PDF="306091" &gt; PDF=306000 MemberID=91 &lt;/weight&gt;
#&lt;weight id="1102" MUR="1.0" MUF="1.0" PDF="306092" &gt; PDF=306000 MemberID=92 &lt;/weight&gt;
#&lt;weight id="1103" MUR="1.0" MUF="1.0" PDF="306093" &gt; PDF=306000 MemberID=93 &lt;/weight&gt;
#&lt;weight id="1104" MUR="1.0" MUF="1.0" PDF="306094" &gt; PDF=306000 MemberID=94 &lt;/weight&gt;
#&lt;weight id="1105" MUR="1.0" MUF="1.0" PDF="306095" &gt; PDF=306000 MemberID=95 &lt;/weight&gt;
#&lt;weight id="1106" MUR="1.0" MUF="1.0" PDF="306096" &gt; PDF=306000 MemberID=96 &lt;/weight&gt;
#&lt;weight id="1107" MUR="1.0" MUF="1.0" PDF="306097" &gt; PDF=306000 MemberID=97 &lt;/weight&gt;
#&lt;weight id="1108" MUR="1.0" MUF="1.0" PDF="306098" &gt; PDF=306000 MemberID=98 &lt;/weight&gt;
#&lt;weight id="1109" MUR="1.0" MUF="1.0" PDF="306099" &gt; PDF=306000 MemberID=99 &lt;/weight&gt;
#&lt;weight id="1110" MUR="1.0" MUF="1.0" PDF="306100" &gt; PDF=306000 MemberID=100 &lt;/weight&gt;
#&lt;weight id="1111" MUR="1.0" MUF="1.0" PDF="306101" &gt; PDF=306000 MemberID=101 &lt;/weight&gt;
#&lt;weight id="1112" MUR="1.0" MUF="1.0" PDF="306102" &gt; PDF=306000 MemberID=102 &lt;/weight&gt;






#DY 2018
#&lt;weight id="1010" MUR="1.0" MUF="1.0" PDF="306000" &gt;  &lt;/weight&gt;
#&lt;weight id="1011" MUR="1.0" MUF="1.0" PDF="306001" &gt; PDF=306000 MemberID=1 &lt;/weight&gt;
#&lt;weight id="1012" MUR="1.0" MUF="1.0" PDF="306002" &gt; PDF=306000 MemberID=2 &lt;/weight&gt;
#&lt;weight id="1013" MUR="1.0" MUF="1.0" PDF="306003" &gt; PDF=306000 MemberID=3 &lt;/weight&gt;
#&lt;weight id="1014" MUR="1.0" MUF="1.0" PDF="306004" &gt; PDF=306000 MemberID=4 &lt;/weight&gt;
#&lt;weight id="1015" MUR="1.0" MUF="1.0" PDF="306005" &gt; PDF=306000 MemberID=5 &lt;/weight&gt;
#&lt;weight id="1016" MUR="1.0" MUF="1.0" PDF="306006" &gt; PDF=306000 MemberID=6 &lt;/weight&gt;
#&lt;weight id="1017" MUR="1.0" MUF="1.0" PDF="306007" &gt; PDF=306000 MemberID=7 &lt;/weight&gt;
#&lt;weight id="1018" MUR="1.0" MUF="1.0" PDF="306008" &gt; PDF=306000 MemberID=8 &lt;/weight&gt;
#&lt;weight id="1019" MUR="1.0" MUF="1.0" PDF="306009" &gt; PDF=306000 MemberID=9 &lt;/weight&gt;
#&lt;weight id="1020" MUR="1.0" MUF="1.0" PDF="306010" &gt; PDF=306000 MemberID=10 &lt;/weight&gt;
#&lt;weight id="1021" MUR="1.0" MUF="1.0" PDF="306011" &gt; PDF=306000 MemberID=11 &lt;/weight&gt;
#&lt;weight id="1022" MUR="1.0" MUF="1.0" PDF="306012" &gt; PDF=306000 MemberID=12 &lt;/weight&gt;
#&lt;weight id="1023" MUR="1.0" MUF="1.0" PDF="306013" &gt; PDF=306000 MemberID=13 &lt;/weight&gt;
#&lt;weight id="1024" MUR="1.0" MUF="1.0" PDF="306014" &gt; PDF=306000 MemberID=14 &lt;/weight&gt;
#&lt;weight id="1025" MUR="1.0" MUF="1.0" PDF="306015" &gt; PDF=306000 MemberID=15 &lt;/weight&gt;
#&lt;weight id="1026" MUR="1.0" MUF="1.0" PDF="306016" &gt; PDF=306000 MemberID=16 &lt;/weight&gt;
#&lt;weight id="1027" MUR="1.0" MUF="1.0" PDF="306017" &gt; PDF=306000 MemberID=17 &lt;/weight&gt;
#&lt;weight id="1028" MUR="1.0" MUF="1.0" PDF="306018" &gt; PDF=306000 MemberID=18 &lt;/weight&gt;
#&lt;weight id="1029" MUR="1.0" MUF="1.0" PDF="306019" &gt; PDF=306000 MemberID=19 &lt;/weight&gt;
#&lt;weight id="1030" MUR="1.0" MUF="1.0" PDF="306020" &gt; PDF=306000 MemberID=20 &lt;/weight&gt;
#&lt;weight id="1031" MUR="1.0" MUF="1.0" PDF="306021" &gt; PDF=306000 MemberID=21 &lt;/weight&gt;
#&lt;weight id="1032" MUR="1.0" MUF="1.0" PDF="306022" &gt; PDF=306000 MemberID=22 &lt;/weight&gt;
#&lt;weight id="1033" MUR="1.0" MUF="1.0" PDF="306023" &gt; PDF=306000 MemberID=23 &lt;/weight&gt;
#&lt;weight id="1034" MUR="1.0" MUF="1.0" PDF="306024" &gt; PDF=306000 MemberID=24 &lt;/weight&gt;
#&lt;weight id="1035" MUR="1.0" MUF="1.0" PDF="306025" &gt; PDF=306000 MemberID=25 &lt;/weight&gt;
#&lt;weight id="1036" MUR="1.0" MUF="1.0" PDF="306026" &gt; PDF=306000 MemberID=26 &lt;/weight&gt;
#&lt;weight id="1037" MUR="1.0" MUF="1.0" PDF="306027" &gt; PDF=306000 MemberID=27 &lt;/weight&gt;
#&lt;weight id="1038" MUR="1.0" MUF="1.0" PDF="306028" &gt; PDF=306000 MemberID=28 &lt;/weight&gt;
#&lt;weight id="1039" MUR="1.0" MUF="1.0" PDF="306029" &gt; PDF=306000 MemberID=29 &lt;/weight&gt;
#&lt;weight id="1040" MUR="1.0" MUF="1.0" PDF="306030" &gt; PDF=306000 MemberID=30 &lt;/weight&gt;
#&lt;weight id="1041" MUR="1.0" MUF="1.0" PDF="306031" &gt; PDF=306000 MemberID=31 &lt;/weight&gt;
#&lt;weight id="1042" MUR="1.0" MUF="1.0" PDF="306032" &gt; PDF=306000 MemberID=32 &lt;/weight&gt;
#&lt;weight id="1043" MUR="1.0" MUF="1.0" PDF="306033" &gt; PDF=306000 MemberID=33 &lt;/weight&gt;
#&lt;weight id="1044" MUR="1.0" MUF="1.0" PDF="306034" &gt; PDF=306000 MemberID=34 &lt;/weight&gt;
#&lt;weight id="1045" MUR="1.0" MUF="1.0" PDF="306035" &gt; PDF=306000 MemberID=35 &lt;/weight&gt;
#&lt;weight id="1046" MUR="1.0" MUF="1.0" PDF="306036" &gt; PDF=306000 MemberID=36 &lt;/weight&gt;
#&lt;weight id="1047" MUR="1.0" MUF="1.0" PDF="306037" &gt; PDF=306000 MemberID=37 &lt;/weight&gt;
#&lt;weight id="1048" MUR="1.0" MUF="1.0" PDF="306038" &gt; PDF=306000 MemberID=38 &lt;/weight&gt;
#&lt;weight id="1049" MUR="1.0" MUF="1.0" PDF="306039" &gt; PDF=306000 MemberID=39 &lt;/weight&gt;
#&lt;weight id="1050" MUR="1.0" MUF="1.0" PDF="306040" &gt; PDF=306000 MemberID=40 &lt;/weight&gt;
#&lt;weight id="1051" MUR="1.0" MUF="1.0" PDF="306041" &gt; PDF=306000 MemberID=41 &lt;/weight&gt;
#&lt;weight id="1052" MUR="1.0" MUF="1.0" PDF="306042" &gt; PDF=306000 MemberID=42 &lt;/weight&gt;
#&lt;weight id="1053" MUR="1.0" MUF="1.0" PDF="306043" &gt; PDF=306000 MemberID=43 &lt;/weight&gt;
#&lt;weight id="1054" MUR="1.0" MUF="1.0" PDF="306044" &gt; PDF=306000 MemberID=44 &lt;/weight&gt;
#&lt;weight id="1055" MUR="1.0" MUF="1.0" PDF="306045" &gt; PDF=306000 MemberID=45 &lt;/weight&gt;
#&lt;weight id="1056" MUR="1.0" MUF="1.0" PDF="306046" &gt; PDF=306000 MemberID=46 &lt;/weight&gt;
#&lt;weight id="1057" MUR="1.0" MUF="1.0" PDF="306047" &gt; PDF=306000 MemberID=47 &lt;/weight&gt;
#&lt;weight id="1058" MUR="1.0" MUF="1.0" PDF="306048" &gt; PDF=306000 MemberID=48 &lt;/weight&gt;
#&lt;weight id="1059" MUR="1.0" MUF="1.0" PDF="306049" &gt; PDF=306000 MemberID=49 &lt;/weight&gt;
#&lt;weight id="1060" MUR="1.0" MUF="1.0" PDF="306050" &gt; PDF=306000 MemberID=50 &lt;/weight&gt;
#&lt;weight id="1061" MUR="1.0" MUF="1.0" PDF="306051" &gt; PDF=306000 MemberID=51 &lt;/weight&gt;
#&lt;weight id="1062" MUR="1.0" MUF="1.0" PDF="306052" &gt; PDF=306000 MemberID=52 &lt;/weight&gt;
#&lt;weight id="1063" MUR="1.0" MUF="1.0" PDF="306053" &gt; PDF=306000 MemberID=53 &lt;/weight&gt;
#&lt;weight id="1064" MUR="1.0" MUF="1.0" PDF="306054" &gt; PDF=306000 MemberID=54 &lt;/weight&gt;
#&lt;weight id="1065" MUR="1.0" MUF="1.0" PDF="306055" &gt; PDF=306000 MemberID=55 &lt;/weight&gt;
#&lt;weight id="1066" MUR="1.0" MUF="1.0" PDF="306056" &gt; PDF=306000 MemberID=56 &lt;/weight&gt;
#&lt;weight id="1067" MUR="1.0" MUF="1.0" PDF="306057" &gt; PDF=306000 MemberID=57 &lt;/weight&gt;
#&lt;weight id="1068" MUR="1.0" MUF="1.0" PDF="306058" &gt; PDF=306000 MemberID=58 &lt;/weight&gt;
#&lt;weight id="1069" MUR="1.0" MUF="1.0" PDF="306059" &gt; PDF=306000 MemberID=59 &lt;/weight&gt;
#&lt;weight id="1070" MUR="1.0" MUF="1.0" PDF="306060" &gt; PDF=306000 MemberID=60 &lt;/weight&gt;
#&lt;weight id="1071" MUR="1.0" MUF="1.0" PDF="306061" &gt; PDF=306000 MemberID=61 &lt;/weight&gt;
#&lt;weight id="1072" MUR="1.0" MUF="1.0" PDF="306062" &gt; PDF=306000 MemberID=62 &lt;/weight&gt;
#&lt;weight id="1073" MUR="1.0" MUF="1.0" PDF="306063" &gt; PDF=306000 MemberID=63 &lt;/weight&gt;
#&lt;weight id="1074" MUR="1.0" MUF="1.0" PDF="306064" &gt; PDF=306000 MemberID=64 &lt;/weight&gt;
#&lt;weight id="1075" MUR="1.0" MUF="1.0" PDF="306065" &gt; PDF=306000 MemberID=65 &lt;/weight&gt;
#&lt;weight id="1076" MUR="1.0" MUF="1.0" PDF="306066" &gt; PDF=306000 MemberID=66 &lt;/weight&gt;
#&lt;weight id="1077" MUR="1.0" MUF="1.0" PDF="306067" &gt; PDF=306000 MemberID=67 &lt;/weight&gt;
#&lt;weight id="1078" MUR="1.0" MUF="1.0" PDF="306068" &gt; PDF=306000 MemberID=68 &lt;/weight&gt;
#&lt;weight id="1079" MUR="1.0" MUF="1.0" PDF="306069" &gt; PDF=306000 MemberID=69 &lt;/weight&gt;
#&lt;weight id="1080" MUR="1.0" MUF="1.0" PDF="306070" &gt; PDF=306000 MemberID=70 &lt;/weight&gt;
#&lt;weight id="1081" MUR="1.0" MUF="1.0" PDF="306071" &gt; PDF=306000 MemberID=71 &lt;/weight&gt;
#&lt;weight id="1082" MUR="1.0" MUF="1.0" PDF="306072" &gt; PDF=306000 MemberID=72 &lt;/weight&gt;
#&lt;weight id="1083" MUR="1.0" MUF="1.0" PDF="306073" &gt; PDF=306000 MemberID=73 &lt;/weight&gt;
#&lt;weight id="1084" MUR="1.0" MUF="1.0" PDF="306074" &gt; PDF=306000 MemberID=74 &lt;/weight&gt;
#&lt;weight id="1085" MUR="1.0" MUF="1.0" PDF="306075" &gt; PDF=306000 MemberID=75 &lt;/weight&gt;
#&lt;weight id="1086" MUR="1.0" MUF="1.0" PDF="306076" &gt; PDF=306000 MemberID=76 &lt;/weight&gt;
#&lt;weight id="1087" MUR="1.0" MUF="1.0" PDF="306077" &gt; PDF=306000 MemberID=77 &lt;/weight&gt;
#&lt;weight id="1088" MUR="1.0" MUF="1.0" PDF="306078" &gt; PDF=306000 MemberID=78 &lt;/weight&gt;
#&lt;weight id="1089" MUR="1.0" MUF="1.0" PDF="306079" &gt; PDF=306000 MemberID=79 &lt;/weight&gt;
#&lt;weight id="1090" MUR="1.0" MUF="1.0" PDF="306080" &gt; PDF=306000 MemberID=80 &lt;/weight&gt;
#&lt;weight id="1091" MUR="1.0" MUF="1.0" PDF="306081" &gt; PDF=306000 MemberID=81 &lt;/weight&gt;
#&lt;weight id="1092" MUR="1.0" MUF="1.0" PDF="306082" &gt; PDF=306000 MemberID=82 &lt;/weight&gt;
#&lt;weight id="1093" MUR="1.0" MUF="1.0" PDF="306083" &gt; PDF=306000 MemberID=83 &lt;/weight&gt;
#&lt;weight id="1094" MUR="1.0" MUF="1.0" PDF="306084" &gt; PDF=306000 MemberID=84 &lt;/weight&gt;
#&lt;weight id="1095" MUR="1.0" MUF="1.0" PDF="306085" &gt; PDF=306000 MemberID=85 &lt;/weight&gt;
#&lt;weight id="1096" MUR="1.0" MUF="1.0" PDF="306086" &gt; PDF=306000 MemberID=86 &lt;/weight&gt;
#&lt;weight id="1097" MUR="1.0" MUF="1.0" PDF="306087" &gt; PDF=306000 MemberID=87 &lt;/weight&gt;
#&lt;weight id="1098" MUR="1.0" MUF="1.0" PDF="306088" &gt; PDF=306000 MemberID=88 &lt;/weight&gt;
#&lt;weight id="1099" MUR="1.0" MUF="1.0" PDF="306089" &gt; PDF=306000 MemberID=89 &lt;/weight&gt;
#&lt;weight id="1100" MUR="1.0" MUF="1.0" PDF="306090" &gt; PDF=306000 MemberID=90 &lt;/weight&gt;
#&lt;weight id="1101" MUR="1.0" MUF="1.0" PDF="306091" &gt; PDF=306000 MemberID=91 &lt;/weight&gt;
#&lt;weight id="1102" MUR="1.0" MUF="1.0" PDF="306092" &gt; PDF=306000 MemberID=92 &lt;/weight&gt;
#&lt;weight id="1103" MUR="1.0" MUF="1.0" PDF="306093" &gt; PDF=306000 MemberID=93 &lt;/weight&gt;
#&lt;weight id="1104" MUR="1.0" MUF="1.0" PDF="306094" &gt; PDF=306000 MemberID=94 &lt;/weight&gt;
#&lt;weight id="1105" MUR="1.0" MUF="1.0" PDF="306095" &gt; PDF=306000 MemberID=95 &lt;/weight&gt;
#&lt;weight id="1106" MUR="1.0" MUF="1.0" PDF="306096" &gt; PDF=306000 MemberID=96 &lt;/weight&gt;
#&lt;weight id="1107" MUR="1.0" MUF="1.0" PDF="306097" &gt; PDF=306000 MemberID=97 &lt;/weight&gt;
#&lt;weight id="1108" MUR="1.0" MUF="1.0" PDF="306098" &gt; PDF=306000 MemberID=98 &lt;/weight&gt;
#&lt;weight id="1109" MUR="1.0" MUF="1.0" PDF="306099" &gt; PDF=306000 MemberID=99 &lt;/weight&gt;
#&lt;weight id="1110" MUR="1.0" MUF="1.0" PDF="306100" &gt; PDF=306000 MemberID=100 &lt;/weight&gt;
#&lt;weight id="1111" MUR="1.0" MUF="1.0" PDF="306101" &gt; PDF=306000 MemberID=101 &lt;/weight&gt;
#&lt;weight id="1112" MUR="1.0" MUF="1.0" PDF="306102" &gt; PDF=306000 MemberID=102 &lt;/weight&gt;




#
#
#TT 2016
#weightgroup combine="hessian" name="PDF_variation">
#<weight id="2001"> PDF set = 260001 </weight>
#<weight id="2002"> PDF set = 260002 </weight>
#<weight id="2003"> PDF set = 260003 </weight>
#<weight id="2004"> PDF set = 260004 </weight>
#<weight id="2005"> PDF set = 260005 </weight>
#<weight id="2006"> PDF set = 260006 </weight>
#<weight id="2007"> PDF set = 260007 </weight>
#<weight id="2008"> PDF set = 260008 </weight>
#<weight id="2009"> PDF set = 260009 </weight>
#<weight id="2010"> PDF set = 260010 </weight>
#<weight id="2011"> PDF set = 260011 </weight>
#<weight id="2012"> PDF set = 260012 </weight>
#<weight id="2013"> PDF set = 260013 </weight>
#<weight id="2014"> PDF set = 260014 </weight>
#<weight id="2015"> PDF set = 260015 </weight>
#<weight id="2016"> PDF set = 260016 </weight>
#<weight id="2017"> PDF set = 260017 </weight>
#<weight id="2018"> PDF set = 260018 </weight>
#<weight id="2019"> PDF set = 260019 </weight>
#<weight id="2020"> PDF set = 260020 </weight>
#<weight id="2021"> PDF set = 260021 </weight>
#<weight id="2022"> PDF set = 260022 </weight>
#<weight id="2023"> PDF set = 260023 </weight>
#<weight id="2024"> PDF set = 260024 </weight>
#<weight id="2025"> PDF set = 260025 </weight>
#<weight id="2026"> PDF set = 260026 </weight>
#<weight id="2027"> PDF set = 260027 </weight>
#<weight id="2028"> PDF set = 260028 </weight>
#<weight id="2029"> PDF set = 260029 </weight>
#<weight id="2030"> PDF set = 260030 </weight>
#<weight id="2031"> PDF set = 260031 </weight>
#<weight id="2032"> PDF set = 260032 </weight>
#<weight id="2033"> PDF set = 260033 </weight>
#<weight id="2034"> PDF set = 260034 </weight>
#<weight id="2035"> PDF set = 260035 </weight>
#<weight id="2036"> PDF set = 260036 </weight>
#<weight id="2037"> PDF set = 260037 </weight>
#<weight id="2038"> PDF set = 260038 </weight>
#<weight id="2039"> PDF set = 260039 </weight>
#<weight id="2040"> PDF set = 260040 </weight>
#<weight id="2041"> PDF set = 260041 </weight>
#<weight id="2042"> PDF set = 260042 </weight>
#<weight id="2043"> PDF set = 260043 </weight>
#<weight id="2044"> PDF set = 260044 </weight>
#<weight id="2045"> PDF set = 260045 </weight>
#<weight id="2046"> PDF set = 260046 </weight>
#<weight id="2047"> PDF set = 260047 </weight>
#<weight id="2048"> PDF set = 260048 </weight>
#<weight id="2049"> PDF set = 260049 </weight>
#<weight id="2050"> PDF set = 260050 </weight>
#<weight id="2051"> PDF set = 260051 </weight>
#<weight id="2052"> PDF set = 260052 </weight>
#<weight id="2053"> PDF set = 260053 </weight>
#<weight id="2054"> PDF set = 260054 </weight>
#<weight id="2055"> PDF set = 260055 </weight>
#<weight id="2056"> PDF set = 260056 </weight>
#<weight id="2057"> PDF set = 260057 </weight>
#<weight id="2058"> PDF set = 260058 </weight>
#<weight id="2059"> PDF set = 260059 </weight>
#<weight id="2060"> PDF set = 260060 </weight>
#<weight id="2061"> PDF set = 260061 </weight>
#<weight id="2062"> PDF set = 260062 </weight>
#<weight id="2063"> PDF set = 260063 </weight>
#<weight id="2064"> PDF set = 260064 </weight>
#<weight id="2065"> PDF set = 260065 </weight>
#<weight id="2066"> PDF set = 260066 </weight>
#<weight id="2067"> PDF set = 260067 </weight>
#<weight id="2068"> PDF set = 260068 </weight>
#<weight id="2069"> PDF set = 260069 </weight>
#<weight id="2070"> PDF set = 260070 </weight>
#<weight id="2071"> PDF set = 260071 </weight>
#<weight id="2072"> PDF set = 260072 </weight>
#<weight id="2073"> PDF set = 260073 </weight>
#<weight id="2074"> PDF set = 260074 </weight>
#<weight id="2075"> PDF set = 260075 </weight>
#<weight id="2076"> PDF set = 260076 </weight>
#<weight id="2077"> PDF set = 260077 </weight>
#<weight id="2078"> PDF set = 260078 </weight>
#<weight id="2079"> PDF set = 260079 </weight>
#<weight id="2080"> PDF set = 260080 </weight>
#<weight id="2081"> PDF set = 260081 </weight>
#<weight id="2082"> PDF set = 260082 </weight>
#<weight id="2083"> PDF set = 260083 </weight>
#<weight id="2084"> PDF set = 260084 </weight>
#<weight id="2085"> PDF set = 260085 </weight>
#<weight id="2086"> PDF set = 260086 </weight>
#<weight id="2087"> PDF set = 260087 </weight>
#<weight id="2088"> PDF set = 260088 </weight>
#<weight id="2089"> PDF set = 260089 </weight>
#<weight id="2090"> PDF set = 260090 </weight>
#<weight id="2091"> PDF set = 260091 </weight>
#<weight id="2092"> PDF set = 260092 </weight>
#<weight id="2093"> PDF set = 260093 </weight>
#<weight id="2094"> PDF set = 260094 </weight>
#<weight id="2095"> PDF set = 260095 </weight>
#<weight id="2096"> PDF set = 260096 </weight>
#<weight id="2097"> PDF set = 260097 </weight>
#<weight id="2098"> PDF set = 260098 </weight>
#<weight id="2099"> PDF set = 260099 </weight>
#<weight id="2100"> PDF set = 260100 </weight>
#<weight id="2101"> PDF set = 265000 </weight>
#<weight id="2102"> PDF set = 266000 </weight>
#<weight id="3001"> PDF set = 13100 </weight>
#<weight id="3002"> PDF set = 13101 </weight>
#<weight id="3003"> PDF set = 13102 </weight>
#<weight id="3004"> PDF set = 13103 </weight>
#<weight id="3005"> PDF set = 13104 </weight>
#<weight id="3006"> PDF set = 13105 </weight>
#<weight id="3007"> PDF set = 13106 </weight>
#<weight id="3008"> PDF set = 13107 </weight>
#<weight id="3009"> PDF set = 13108 </weight>
#<weight id="3010"> PDF set = 13109 </weight>
#<weight id="3011"> PDF set = 13110 </weight>
#<weight id="3012"> PDF set = 13111 </weight>
#<weight id="3013"> PDF set = 13112 </weight>
#<weight id="3014"> PDF set = 13113 </weight>
#<weight id="3015"> PDF set = 13114 </weight>
#<weight id="3016"> PDF set = 13115 </weight>
#<weight id="3017"> PDF set = 13116 </weight>
#<weight id="3018"> PDF set = 13117 </weight>
#<weight id="3019"> PDF set = 13118 </weight>
#<weight id="3020"> PDF set = 13119 </weight>
#<weight id="3021"> PDF set = 13120 </weight>
#<weight id="3022"> PDF set = 13121 </weight>
#<weight id="3023"> PDF set = 13122 </weight>
#<weight id="3024"> PDF set = 13123 </weight>
#<weight id="3025"> PDF set = 13124 </weight>
#<weight id="3026"> PDF set = 13125 </weight>
#<weight id="3027"> PDF set = 13126 </weight>
#<weight id="3028"> PDF set = 13127 </weight>
#<weight id="3029"> PDF set = 13128 </weight>
#<weight id="3030"> PDF set = 13129 </weight>
#<weight id="3031"> PDF set = 13130 </weight>
#<weight id="3032"> PDF set = 13131 </weight>
#<weight id="3033"> PDF set = 13132 </weight>
#<weight id="3034"> PDF set = 13133 </weight>
#<weight id="3035"> PDF set = 13134 </weight>
#<weight id="3036"> PDF set = 13135 </weight>
#<weight id="3037"> PDF set = 13136 </weight>
#<weight id="3038"> PDF set = 13137 </weight>
#<weight id="3039"> PDF set = 13138 </weight>
#<weight id="3040"> PDF set = 13139 </weight>
#<weight id="3041"> PDF set = 13140 </weight>
#<weight id="3042"> PDF set = 13141 </weight>
#<weight id="3043"> PDF set = 13142 </weight>
#<weight id="3044"> PDF set = 13143 </weight>
#<weight id="3045"> PDF set = 13144 </weight>
#<weight id="3046"> PDF set = 13145 </weight>
#<weight id="3047"> PDF set = 13146 </weight>
#<weight id="3048"> PDF set = 13147 </weight>
#<weight id="3049"> PDF set = 13148 </weight>
#<weight id="3050"> PDF set = 13149 </weight>
#<weight id="3051"> PDF set = 13150 </weight>
#<weight id="3052"> PDF set = 13151 </weight>
#<weight id="3053"> PDF set = 13152 </weight>
#<weight id="3054"> PDF set = 13153 </weight>
#<weight id="3055"> PDF set = 13154 </weight>
#<weight id="3056"> PDF set = 13155 </weight>
#<weight id="3057"> PDF set = 13156 </weight>
#<weight id="3058"> PDF set = 13164 </weight>
#<weight id="3059"> PDF set = 13166 </weight>
#<weight id="3060"> PDF set = 11000 </weight>
#<weight id="4001"> PDF set = 25200 </weight>
#<weight id="4002"> PDF set = 25201 </weight>
#<weight id="4003"> PDF set = 25202 </weight>
#<weight id="4004"> PDF set = 25203 </weight>
#<weight id="4005"> PDF set = 25204 </weight>
#<weight id="4006"> PDF set = 25205 </weight>
#<weight id="4007"> PDF set = 25206 </weight>
#<weight id="4008"> PDF set = 25207 </weight>
#<weight id="4009"> PDF set = 25208 </weight>
#<weight id="4010"> PDF set = 25209 </weight>
#<weight id="4011"> PDF set = 25210 </weight>
#<weight id="4012"> PDF set = 25211 </weight>
#<weight id="4013"> PDF set = 25212 </weight>
#<weight id="4014"> PDF set = 25213 </weight>
#<weight id="4015"> PDF set = 25214 </weight>
#<weight id="4016"> PDF set = 25215 </weight>
#<weight id="4017"> PDF set = 25216 </weight>
#<weight id="4018"> PDF set = 25217 </weight>
#<weight id="4019"> PDF set = 25218 </weight>
#<weight id="4020"> PDF set = 25219 </weight>
#<weight id="4021"> PDF set = 25220 </weight>
#<weight id="4022"> PDF set = 25221 </weight>
#<weight id="4023"> PDF set = 25222 </weight>
#<weight id="4024"> PDF set = 25223 </weight>
#<weight id="4025"> PDF set = 25224 </weight>
#<weight id="4026"> PDF set = 25225 </weight>
#<weight id="4027"> PDF set = 25226 </weight>
#<weight id="4028"> PDF set = 25227 </weight>
#<weight id="4029"> PDF set = 25228 </weight>
#<weight id="4030"> PDF set = 25229 </weight>
#<weight id="4031"> PDF set = 25230 </weight>
#<weight id="4032"> PDF set = 25231 </weight>
#<weight id="4033"> PDF set = 25232 </weight>
#<weight id="4034"> PDF set = 25233 </weight>
#<weight id="4035"> PDF set = 25234 </weight>
#<weight id="4036"> PDF set = 25235 </weight>
#<weight id="4037"> PDF set = 25236 </weight>
#<weight id="4038"> PDF set = 25237 </weight>
#<weight id="4039"> PDF set = 25238 </weight>
#<weight id="4040"> PDF set = 25239 </weight>
#<weight id="4041"> PDF set = 25240 </weight>
#<weight id="4042"> PDF set = 25241 </weight>
#<weight id="4043"> PDF set = 25242 </weight>
#<weight id="4044"> PDF set = 25243 </weight>
#<weight id="4045"> PDF set = 25244 </weight>
#<weight id="4046"> PDF set = 25245 </weight>
#<weight id="4047"> PDF set = 25246 </weight>
#<weight id="4048"> PDF set = 25247 </weight>
#<weight id="4049"> PDF set = 25248 </weight>
#<weight id="4050"> PDF set = 25249 </weight>
#<weight id="4051"> PDF set = 25250 </weight>
#<weight id="4052"> PDF set = 25260 </weight>
#<weight id="4053"> PDF set = 25261 </weight>
#<weight id="4054"> PDF set = 25262 </weight>
#<weight id="4055"> PDF set = 25263 </weight>
#<weight id="4056"> PDF set = 25264 </weight>










# TT 2017
#weightgroup combine="hessian" name="PDF_variation1">
#<weight id="2000"> lhapdf=306000 </weight>
#<weight id="2001"> lhapdf=306001 </weight>
#<weight id="2002"> lhapdf=306002 </weight>
#<weight id="2003"> lhapdf=306003 </weight>
#<weight id="2004"> lhapdf=306004 </weight>
#<weight id="2005"> lhapdf=306005 </weight>
#<weight id="2006"> lhapdf=306006 </weight>
#<weight id="2007"> lhapdf=306007 </weight>
#<weight id="2008"> lhapdf=306008 </weight>
#<weight id="2009"> lhapdf=306009 </weight>
#<weight id="2010"> lhapdf=306010 </weight>
#<weight id="2011"> lhapdf=306011 </weight>
#<weight id="2012"> lhapdf=306012 </weight>
#<weight id="2013"> lhapdf=306013 </weight>
#<weight id="2014"> lhapdf=306014 </weight>
#<weight id="2015"> lhapdf=306015 </weight>
#<weight id="2016"> lhapdf=306016 </weight>
#<weight id="2017"> lhapdf=306017 </weight>
#<weight id="2018"> lhapdf=306018 </weight>
#<weight id="2019"> lhapdf=306019 </weight>
#<weight id="2020"> lhapdf=306020 </weight>
#<weight id="2021"> lhapdf=306021 </weight>
#<weight id="2022"> lhapdf=306022 </weight>
#<weight id="2023"> lhapdf=306023 </weight>
#<weight id="2024"> lhapdf=306024 </weight>
#<weight id="2025"> lhapdf=306025 </weight>
#<weight id="2026"> lhapdf=306026 </weight>
#<weight id="2027"> lhapdf=306027 </weight>
#<weight id="2028"> lhapdf=306028 </weight>
#<weight id="2029"> lhapdf=306029 </weight>
#<weight id="2030"> lhapdf=306030 </weight>
#<weight id="2031"> lhapdf=306031 </weight>
#<weight id="2032"> lhapdf=306032 </weight>
#<weight id="2033"> lhapdf=306033 </weight>
#<weight id="2034"> lhapdf=306034 </weight>
#<weight id="2035"> lhapdf=306035 </weight>
#<weight id="2036"> lhapdf=306036 </weight>
#<weight id="2037"> lhapdf=306037 </weight>
#<weight id="2038"> lhapdf=306038 </weight>
#<weight id="2039"> lhapdf=306039 </weight>
#<weight id="2040"> lhapdf=306040 </weight>
#<weight id="2041"> lhapdf=306041 </weight>
#<weight id="2042"> lhapdf=306042 </weight>
#<weight id="2043"> lhapdf=306043 </weight>
#<weight id="2044"> lhapdf=306044 </weight>
#<weight id="2045"> lhapdf=306045 </weight>
#<weight id="2046"> lhapdf=306046 </weight>
#<weight id="2047"> lhapdf=306047 </weight>
#<weight id="2048"> lhapdf=306048 </weight>
#<weight id="2049"> lhapdf=306049 </weight>
#<weight id="2050"> lhapdf=306050 </weight>
#<weight id="2051"> lhapdf=306051 </weight>
#<weight id="2052"> lhapdf=306052 </weight>
#<weight id="2053"> lhapdf=306053 </weight>
#<weight id="2054"> lhapdf=306054 </weight>
#<weight id="2055"> lhapdf=306055 </weight>
#<weight id="2056"> lhapdf=306056 </weight>
#<weight id="2057"> lhapdf=306057 </weight>
#<weight id="2058"> lhapdf=306058 </weight>
#<weight id="2059"> lhapdf=306059 </weight>
#<weight id="2060"> lhapdf=306060 </weight>
#<weight id="2061"> lhapdf=306061 </weight>
#<weight id="2062"> lhapdf=306062 </weight>
#<weight id="2063"> lhapdf=306063 </weight>
#<weight id="2064"> lhapdf=306064 </weight>
#<weight id="2065"> lhapdf=306065 </weight>
#<weight id="2066"> lhapdf=306066 </weight>
#<weight id="2067"> lhapdf=306067 </weight>
#<weight id="2068"> lhapdf=306068 </weight>
#<weight id="2069"> lhapdf=306069 </weight>
#<weight id="2070"> lhapdf=306070 </weight>
#<weight id="2071"> lhapdf=306071 </weight>
#<weight id="2072"> lhapdf=306072 </weight>
#<weight id="2073"> lhapdf=306073 </weight>
#<weight id="2074"> lhapdf=306074 </weight>
#<weight id="2075"> lhapdf=306075 </weight>
#<weight id="2076"> lhapdf=306076 </weight>
#<weight id="2077"> lhapdf=306077 </weight>
#<weight id="2078"> lhapdf=306078 </weight>
#<weight id="2079"> lhapdf=306079 </weight>
#<weight id="2080"> lhapdf=306080 </weight>
#<weight id="2081"> lhapdf=306081 </weight>
#<weight id="2082"> lhapdf=306082 </weight>
#<weight id="2083"> lhapdf=306083 </weight>
#<weight id="2084"> lhapdf=306084 </weight>
#<weight id="2085"> lhapdf=306085 </weight>
#<weight id="2086"> lhapdf=306086 </weight>
#<weight id="2087"> lhapdf=306087 </weight>
#<weight id="2088"> lhapdf=306088 </weight>
#<weight id="2089"> lhapdf=306089 </weight>
#<weight id="2090"> lhapdf=306090 </weight>
#<weight id="2091"> lhapdf=306091 </weight>
#<weight id="2092"> lhapdf=306092 </weight>
#<weight id="2093"> lhapdf=306093 </weight>
#<weight id="2094"> lhapdf=306094 </weight>
#<weight id="2095"> lhapdf=306095 </weight>
#<weight id="2096"> lhapdf=306096 </weight>
#<weight id="2097"> lhapdf=306097 </weight>
#<weight id="2098"> lhapdf=306098 </weight>
#<weight id="2099"> lhapdf=306099 </weight>
#<weight id="2100"> lhapdf=306100 </weight>
#<weight id="2101"> lhapdf=306101 </weight>
#<weight id="2102"> lhapdf=306102 </weight>
#<weight id="2104"> lhapdf=322500 </weight>
#<weight id="2105"> lhapdf=322700 </weight>
#<weight id="2106"> lhapdf=322900 </weight>
#<weight id="2107"> lhapdf=323100 </weight>
#<weight id="2108"> lhapdf=323300 </weight>
#<weight id="2109"> lhapdf=323500 </weight>
#<weight id="2110"> lhapdf=323700 </weight>
#<weight id="2111"> lhapdf=323900 </weight>
#<weight id="3000"> lhapdf=305800 </weight>
#<weight id="3001"> lhapdf=305801 </weight>
#<weight id="3002"> lhapdf=305802 </weight>
#<weight id="3003"> lhapdf=305803 </weight>
#<weight id="3004"> lhapdf=305804 </weight>
#<weight id="3005"> lhapdf=305805 </weight>
#<weight id="3006"> lhapdf=305806 </weight>
#<weight id="3007"> lhapdf=305807 </weight>
#<weight id="3008"> lhapdf=305808 </weight>
#<weight id="3009"> lhapdf=305809 </weight>
#<weight id="3010"> lhapdf=305810 </weight>
#<weight id="3011"> lhapdf=305811 </weight>
#<weight id="3012"> lhapdf=305812 </weight>
#<weight id="3013"> lhapdf=305813 </weight>
#<weight id="3014"> lhapdf=305814 </weight>
#<weight id="3015"> lhapdf=305815 </weight>
#<weight id="3016"> lhapdf=305816 </weight>
#<weight id="3017"> lhapdf=305817 </weight>
#<weight id="3018"> lhapdf=305818 </weight>
#<weight id="3019"> lhapdf=305819 </weight>
#<weight id="3020"> lhapdf=305820 </weight>
#<weight id="3021"> lhapdf=305821 </weight>
#<weight id="3022"> lhapdf=305822 </weight>
#<weight id="3023"> lhapdf=305823 </weight>
#<weight id="3024"> lhapdf=305824 </weight>
#<weight id="3025"> lhapdf=305825 </weight>
#<weight id="3026"> lhapdf=305826 </weight>
#<weight id="3027"> lhapdf=305827 </weight>
#<weight id="3028"> lhapdf=305828 </weight>
#<weight id="3029"> lhapdf=305829 </weight>
#<weight id="3030"> lhapdf=305830 </weight>
#<weight id="3031"> lhapdf=305831 </weight>
#<weight id="3032"> lhapdf=305832 </weight>
#<weight id="3033"> lhapdf=305833 </weight>
#<weight id="3034"> lhapdf=305834 </weight>
#<weight id="3035"> lhapdf=305835 </weight>
#<weight id="3036"> lhapdf=305836 </weight>
#<weight id="3037"> lhapdf=305837 </weight>
#<weight id="3038"> lhapdf=305838 </weight>
#<weight id="3039"> lhapdf=305839 </weight>
#<weight id="3040"> lhapdf=305840 </weight>
#<weight id="3041"> lhapdf=305841 </weight>
#<weight id="3042"> lhapdf=305842 </weight>
#<weight id="3043"> lhapdf=305843 </weight>
#<weight id="3044"> lhapdf=305844 </weight>
#<weight id="3045"> lhapdf=305845 </weight>
#<weight id="3046"> lhapdf=305846 </weight>
#<weight id="3047"> lhapdf=305847 </weight>
#<weight id="3048"> lhapdf=305848 </weight>
#<weight id="3049"> lhapdf=305849 </weight>
#<weight id="3050"> lhapdf=305850 </weight>
#<weight id="3051"> lhapdf=305851 </weight>
#<weight id="3052"> lhapdf=305852 </weight>
#<weight id="3053"> lhapdf=305853 </weight>
#<weight id="3054"> lhapdf=305854 </weight>
#<weight id="3055"> lhapdf=305855 </weight>
#<weight id="3056"> lhapdf=305856 </weight>
#<weight id="3057"> lhapdf=305857 </weight>
#<weight id="3058"> lhapdf=305858 </weight>
#<weight id="3059"> lhapdf=305859 </weight>
#<weight id="3060"> lhapdf=305860 </weight>
#<weight id="3061"> lhapdf=305861 </weight>
#<weight id="3062"> lhapdf=305862 </weight>
#<weight id="3063"> lhapdf=305863 </weight>
#<weight id="3064"> lhapdf=305864 </weight>
#<weight id="3065"> lhapdf=305865 </weight>
#<weight id="3066"> lhapdf=305866 </weight>
#<weight id="3067"> lhapdf=305867 </weight>
#<weight id="3068"> lhapdf=305868 </weight>
#<weight id="3069"> lhapdf=305869 </weight>
#<weight id="3070"> lhapdf=305870 </weight>
#<weight id="3071"> lhapdf=305871 </weight>
#<weight id="3072"> lhapdf=305872 </weight>
#<weight id="3073"> lhapdf=305873 </weight>
#<weight id="3074"> lhapdf=305874 </weight>
#<weight id="3075"> lhapdf=305875 </weight>
#<weight id="3076"> lhapdf=305876 </weight>
#<weight id="3077"> lhapdf=305877 </weight>
#<weight id="3078"> lhapdf=305878 </weight>
#<weight id="3079"> lhapdf=305879 </weight>
#<weight id="3080"> lhapdf=305880 </weight>
#<weight id="3081"> lhapdf=305881 </weight>
#<weight id="3082"> lhapdf=305882 </weight>
#<weight id="3083"> lhapdf=305883 </weight>
#<weight id="3084"> lhapdf=305884 </weight>
#<weight id="3085"> lhapdf=305885 </weight>
#<weight id="3086"> lhapdf=305886 </weight>
#<weight id="3087"> lhapdf=305887 </weight>
#<weight id="3088"> lhapdf=305888 </weight>
#<weight id="3089"> lhapdf=305889 </weight>
#<weight id="3090"> lhapdf=305890 </weight>
#<weight id="3091"> lhapdf=305891 </weight>
#<weight id="3092"> lhapdf=305892 </weight>
#<weight id="3093"> lhapdf=305893 </weight>
#<weight id="3094"> lhapdf=305894 </weight>
#<weight id="3095"> lhapdf=305895 </weight>
#<weight id="3096"> lhapdf=305896 </weight>
#<weight id="3097"> lhapdf=305897 </weight>
#<weight id="3098"> lhapdf=305898 </weight>
#<weight id="3099"> lhapdf=305899 </weight>
#<weight id="3100"> lhapdf=305900 </weight>
#<weight id="3101"> lhapdf=305901 </weight>
#<weight id="3102"> lhapdf=305902 </weight>
#<weight id="5000"> lhapdf=13000 </weight>
#<weight id="5001"> lhapdf=13001 </weight>
#<weight id="5002"> lhapdf=13002 </weight>
#<weight id="5003"> lhapdf=13003 </weight>
#<weight id="5004"> lhapdf=13004 </weight>
#<weight id="5005"> lhapdf=13005 </weight>
#<weight id="5006"> lhapdf=13006 </weight>
#<weight id="5007"> lhapdf=13007 </weight>
#<weight id="5008"> lhapdf=13008 </weight>
#<weight id="5009"> lhapdf=13009 </weight>
#<weight id="5010"> lhapdf=13010 </weight>
#<weight id="5011"> lhapdf=13011 </weight>
#<weight id="5012"> lhapdf=13012 </weight>
#<weight id="5013"> lhapdf=13013 </weight>
#<weight id="5014"> lhapdf=13014 </weight>
#<weight id="5015"> lhapdf=13015 </weight>
#<weight id="5016"> lhapdf=13016 </weight>
#<weight id="5017"> lhapdf=13017 </weight>
#<weight id="5018"> lhapdf=13018 </weight>
#<weight id="5019"> lhapdf=13019 </weight>
#<weight id="5020"> lhapdf=13020 </weight>
#<weight id="5021"> lhapdf=13021 </weight>
#<weight id="5022"> lhapdf=13022 </weight>
#<weight id="5023"> lhapdf=13023 </weight>
#<weight id="5024"> lhapdf=13024 </weight>
#<weight id="5025"> lhapdf=13025 </weight>
#<weight id="5026"> lhapdf=13026 </weight>
#<weight id="5027"> lhapdf=13027 </weight>
#<weight id="5028"> lhapdf=13028 </weight>
#<weight id="5029"> lhapdf=13029 </weight>
#<weight id="5030"> lhapdf=13030 </weight>
#<weight id="5031"> lhapdf=13031 </weight>
#<weight id="5032"> lhapdf=13032 </weight>
#<weight id="5033"> lhapdf=13033 </weight>
#<weight id="5034"> lhapdf=13034 </weight>
#<weight id="5035"> lhapdf=13035 </weight>
#<weight id="5036"> lhapdf=13036 </weight>
#<weight id="5037"> lhapdf=13037 </weight>
#<weight id="5038"> lhapdf=13038 </weight>
#<weight id="5039"> lhapdf=13039 </weight>
#<weight id="5040"> lhapdf=13040 </weight>
#<weight id="5041"> lhapdf=13041 </weight>
#<weight id="5042"> lhapdf=13042 </weight>
#<weight id="5043"> lhapdf=13043 </weight>
#<weight id="5044"> lhapdf=13044 </weight>
#<weight id="5045"> lhapdf=13045 </weight>
#<weight id="5046"> lhapdf=13046 </weight>
#<weight id="5047"> lhapdf=13047 </weight>
#<weight id="5048"> lhapdf=13048 </weight>
#<weight id="5049"> lhapdf=13049 </weight>
#<weight id="5050"> lhapdf=13050 </weight>
#<weight id="5051"> lhapdf=13051 </weight>
#<weight id="5052"> lhapdf=13052 </weight>
#<weight id="5053"> lhapdf=13053 </weight>
#<weight id="5054"> lhapdf=13054 </weight>
#<weight id="5055"> lhapdf=13055 </weight>
#<weight id="5056"> lhapdf=13056 </weight>
#<weight id="5060"> lhapdf=13065 </weight>
#<weight id="5070"> lhapdf=13069 </weight>
#<weight id="4000"> lhapdf=13100 </weight>
#<weight id="4001"> lhapdf=13101 </weight>
#<weight id="4002"> lhapdf=13102 </weight>
#<weight id="4003"> lhapdf=13103 </weight>
#<weight id="4004"> lhapdf=13104 </weight>
#<weight id="4005"> lhapdf=13105 </weight>
#<weight id="4006"> lhapdf=13106 </weight>
#<weight id="4007"> lhapdf=13107 </weight>
#<weight id="4008"> lhapdf=13108 </weight>
#<weight id="4009"> lhapdf=13109 </weight>
#<weight id="4010"> lhapdf=13110 </weight>
#<weight id="4011"> lhapdf=13111 </weight>
#<weight id="4012"> lhapdf=13112 </weight>
#<weight id="4013"> lhapdf=13113 </weight>
#<weight id="4014"> lhapdf=13114 </weight>
#<weight id="4015"> lhapdf=13115 </weight>
#<weight id="4016"> lhapdf=13116 </weight>
#<weight id="4017"> lhapdf=13117 </weight>
#<weight id="4018"> lhapdf=13118 </weight>
#<weight id="4019"> lhapdf=13119 </weight>
#<weight id="4020"> lhapdf=13120 </weight>
#<weight id="4021"> lhapdf=13121 </weight>
#<weight id="4022"> lhapdf=13122 </weight>
#<weight id="4023"> lhapdf=13123 </weight>
#<weight id="4024"> lhapdf=13124 </weight>
#<weight id="4025"> lhapdf=13125 </weight>
#<weight id="4026"> lhapdf=13126 </weight>
#<weight id="4027"> lhapdf=13127 </weight>
#<weight id="4028"> lhapdf=13128 </weight>
#<weight id="4029"> lhapdf=13129 </weight>
#<weight id="4030"> lhapdf=13130 </weight>
#<weight id="4031"> lhapdf=13131 </weight>
#<weight id="4032"> lhapdf=13132 </weight>
#<weight id="4033"> lhapdf=13133 </weight>
#<weight id="4034"> lhapdf=13134 </weight>
#<weight id="4035"> lhapdf=13135 </weight>
#<weight id="4036"> lhapdf=13136 </weight>
#<weight id="4037"> lhapdf=13137 </weight>
#<weight id="4038"> lhapdf=13138 </weight>
#<weight id="4039"> lhapdf=13139 </weight>
#<weight id="4040"> lhapdf=13140 </weight>
#<weight id="4041"> lhapdf=13141 </weight>
#<weight id="4042"> lhapdf=13142 </weight>
#<weight id="4043"> lhapdf=13143 </weight>
#<weight id="4044"> lhapdf=13144 </weight>
#<weight id="4045"> lhapdf=13145 </weight>
#<weight id="4046"> lhapdf=13146 </weight>
#<weight id="4047"> lhapdf=13147 </weight>
#<weight id="4048"> lhapdf=13148 </weight>
#<weight id="4049"> lhapdf=13149 </weight>
#<weight id="4050"> lhapdf=13150 </weight>
#<weight id="4051"> lhapdf=13151 </weight>
#<weight id="4052"> lhapdf=13152 </weight>
#<weight id="4053"> lhapdf=13153 </weight>
#<weight id="4054"> lhapdf=13154 </weight>
#<weight id="4055"> lhapdf=13155 </weight>
#<weight id="4056"> lhapdf=13156 </weight>
#<weight id="4060"> lhapdf=13163 </weight>
#<weight id="4070"> lhapdf=13167 </weight>
#<weight id="4080"> lhapdf=13200 </weight>
#<weight id="6000"> lhapdf=25200 </weight>
#<weight id="6001"> lhapdf=25201 </weight>
#<weight id="6002"> lhapdf=25202 </weight>
#<weight id="6003"> lhapdf=25203 </weight>
#<weight id="6004"> lhapdf=25204 </weight>
#<weight id="6005"> lhapdf=25205 </weight>
#<weight id="6006"> lhapdf=25206 </weight>
#<weight id="6007"> lhapdf=25207 </weight>
#<weight id="6008"> lhapdf=25208 </weight>
#<weight id="6009"> lhapdf=25209 </weight>
#<weight id="6010"> lhapdf=25210 </weight>
#<weight id="6011"> lhapdf=25211 </weight>
#<weight id="6012"> lhapdf=25212 </weight>
#<weight id="6013"> lhapdf=25213 </weight>
#<weight id="6014"> lhapdf=25214 </weight>
#<weight id="6015"> lhapdf=25215 </weight>
#<weight id="6016"> lhapdf=25216 </weight>
#<weight id="6017"> lhapdf=25217 </weight>
#<weight id="6018"> lhapdf=25218 </weight>
#<weight id="6019"> lhapdf=25219 </weight>
#<weight id="6020"> lhapdf=25220 </weight>
#<weight id="6021"> lhapdf=25221 </weight>
#<weight id="6022"> lhapdf=25222 </weight>
#<weight id="6023"> lhapdf=25223 </weight>
#<weight id="6024"> lhapdf=25224 </weight>
#<weight id="6025"> lhapdf=25225 </weight>
#<weight id="6026"> lhapdf=25226 </weight>
#<weight id="6027"> lhapdf=25227 </weight>
#<weight id="6028"> lhapdf=25228 </weight>
#<weight id="6029"> lhapdf=25229 </weight>
#<weight id="6030"> lhapdf=25230 </weight>
#<weight id="6031"> lhapdf=25231 </weight>
#<weight id="6032"> lhapdf=25232 </weight>
#<weight id="6033"> lhapdf=25233 </weight>
#<weight id="6034"> lhapdf=25234 </weight>
#<weight id="6035"> lhapdf=25235 </weight>
#<weight id="6036"> lhapdf=25236 </weight>
#<weight id="6037"> lhapdf=25237 </weight>
#<weight id="6038"> lhapdf=25238 </weight>
#<weight id="6039"> lhapdf=25239 </weight>
#<weight id="6040"> lhapdf=25240 </weight>
#<weight id="6041"> lhapdf=25241 </weight>
#<weight id="6042"> lhapdf=25242 </weight>
#<weight id="6043"> lhapdf=25243 </weight>
#<weight id="6044"> lhapdf=25244 </weight>
#<weight id="6045"> lhapdf=25245 </weight>
#<weight id="6046"> lhapdf=25246 </weight>
#<weight id="6047"> lhapdf=25247 </weight>
#<weight id="6048"> lhapdf=25248 </weight>
#<weight id="6049"> lhapdf=25249 </weight>
#<weight id="6050"> lhapdf=25250 </weight>
#<weight id="7000"> lhapdf=25300 </weight>
#<weight id="7001"> lhapdf=25301 </weight>
#<weight id="7002"> lhapdf=25302 </weight>
#<weight id="7003"> lhapdf=25303 </weight>
#<weight id="7004"> lhapdf=25304 </weight>
#<weight id="7005"> lhapdf=25305 </weight>
#<weight id="7006"> lhapdf=25306 </weight>
#<weight id="7007"> lhapdf=25307 </weight>
#<weight id="7008"> lhapdf=25308 </weight>
#<weight id="7009"> lhapdf=25309 </weight>
#<weight id="7010"> lhapdf=25310 </weight>
#<weight id="7011"> lhapdf=25311 </weight>
#<weight id="7012"> lhapdf=25312 </weight>
#<weight id="7013"> lhapdf=25313 </weight>
#<weight id="7014"> lhapdf=25314 </weight>
#<weight id="7015"> lhapdf=25315 </weight>
#<weight id="7016"> lhapdf=25316 </weight>
#<weight id="7017"> lhapdf=25317 </weight>
#<weight id="7018"> lhapdf=25318 </weight>
#<weight id="7019"> lhapdf=25319 </weight>
#<weight id="7020"> lhapdf=25320 </weight>
#<weight id="7021"> lhapdf=25321 </weight>
#<weight id="7022"> lhapdf=25322 </weight>
#<weight id="7023"> lhapdf=25323 </weight>
#<weight id="7024"> lhapdf=25324 </weight>
#<weight id="7025"> lhapdf=25325 </weight>
#<weight id="7026"> lhapdf=25326 </weight>
#<weight id="7027"> lhapdf=25327 </weight>
#<weight id="7028"> lhapdf=25328 </weight>
#<weight id="7029"> lhapdf=25329 </weight>
#<weight id="7030"> lhapdf=25330 </weight>
#<weight id="7031"> lhapdf=25331 </weight>
#<weight id="7032"> lhapdf=25332 </weight>
#<weight id="7033"> lhapdf=25333 </weight>
#<weight id="7034"> lhapdf=25334 </weight>
#<weight id="7035"> lhapdf=25335 </weight>
#<weight id="7036"> lhapdf=25336 </weight>
#<weight id="7037"> lhapdf=25337 </weight>
#<weight id="7038"> lhapdf=25338 </weight>
#<weight id="7039"> lhapdf=25339 </weight>
#<weight id="7040"> lhapdf=25340 </weight>
#<weight id="7041"> lhapdf=25341 </weight>
#<weight id="7042"> lhapdf=25342 </weight>
#<weight id="7043"> lhapdf=25343 </weight>
#<weight id="7044"> lhapdf=25344 </weight>
#<weight id="7045"> lhapdf=25345 </weight>
#<weight id="7046"> lhapdf=25346 </weight>
#<weight id="7047"> lhapdf=25347 </weight>
#<weight id="7048"> lhapdf=25348 </weight>
#<weight id="7049"> lhapdf=25349 </weight>
#<weight id="7050"> lhapdf=25350 </weight>
#<weight id="7060"> lhapdf=25000 </weight>
#<weight id="8000"> lhapdf=42780 </weight>
#<weight id="8001"> lhapdf=42781 </weight>
#<weight id="8002"> lhapdf=42782 </weight>
#<weight id="8003"> lhapdf=42783 </weight>
#<weight id="8004"> lhapdf=42784 </weight>
#<weight id="8005"> lhapdf=42785 </weight>
#<weight id="8006"> lhapdf=42786 </weight>
#<weight id="8007"> lhapdf=42787 </weight>
#<weight id="8008"> lhapdf=42788 </weight>
#<weight id="8009"> lhapdf=42789 </weight>
#<weight id="8010"> lhapdf=42790 </weight>
#<weight id="8011"> lhapdf=42791 </weight>
#<weight id="8012"> lhapdf=42792 </weight>
#<weight id="8013"> lhapdf=42793 </weight>
#<weight id="8014"> lhapdf=42794 </weight>
#<weight id="8015"> lhapdf=42795 </weight>
#<weight id="8016"> lhapdf=42796 </weight>
#<weight id="8017"> lhapdf=42797 </weight>
#<weight id="8018"> lhapdf=42798 </weight>
#<weight id="8019"> lhapdf=42799 </weight>
#<weight id="8020"> lhapdf=42800 </weight>
#<weight id="8021"> lhapdf=42801 </weight>
#<weight id="8022"> lhapdf=42802 </weight>
#<weight id="8023"> lhapdf=42803 </weight>
#<weight id="8024"> lhapdf=42804 </weight>
#<weight id="8025"> lhapdf=42805 </weight>
#<weight id="8026"> lhapdf=42806 </weight>
#<weight id="8027"> lhapdf=42807 </weight>
#<weight id="8028"> lhapdf=42808 </weight>
#<weight id="8029"> lhapdf=42809 </weight>
#<weight id="8500"> lhapdf=90200 </weight>
#<weight id="8501"> lhapdf=90201 </weight>
#<weight id="8502"> lhapdf=90202 </weight>
#<weight id="8503"> lhapdf=90203 </weight>
#<weight id="8504"> lhapdf=90204 </weight>
#<weight id="8505"> lhapdf=90205 </weight>
#<weight id="8506"> lhapdf=90206 </weight>
#<weight id="8507"> lhapdf=90207 </weight>
#<weight id="8508"> lhapdf=90208 </weight>
#<weight id="8509"> lhapdf=90209 </weight>
#<weight id="8510"> lhapdf=90210 </weight>
#<weight id="8511"> lhapdf=90211 </weight>
#<weight id="8512"> lhapdf=90212 </weight>
#<weight id="8513"> lhapdf=90213 </weight>
#<weight id="8514"> lhapdf=90214 </weight>
#<weight id="8515"> lhapdf=90215 </weight>
#<weight id="8516"> lhapdf=90216 </weight>
#<weight id="8517"> lhapdf=90217 </weight>
#<weight id="8518"> lhapdf=90218 </weight>
#<weight id="8519"> lhapdf=90219 </weight>
#<weight id="8520"> lhapdf=90220 </weight>
#<weight id="8521"> lhapdf=90221 </weight>
#<weight id="8522"> lhapdf=90222 </weight>
#<weight id="8523"> lhapdf=90223 </weight>
#<weight id="8524"> lhapdf=90224 </weight>
#<weight id="8525"> lhapdf=90225 </weight>
#<weight id="8526"> lhapdf=90226 </weight>
#<weight id="8527"> lhapdf=90227 </weight>
#<weight id="8528"> lhapdf=90228 </weight>
#<weight id="8529"> lhapdf=90229 </weight>
#<weight id="8530"> lhapdf=90230 </weight>
#<weight id="8531"> lhapdf=90231 </weight>
#<weight id="8532"> lhapdf=90232 </weight>
#<weight id="8533"> lhapdf=90233 </weight>
#<weight id="8534"> lhapdf=90234 </weight>
#<weight id="8535"> lhapdf=90235 </weight>
#<weight id="8536"> lhapdf=90236 </weight>
#<weight id="8537"> lhapdf=90237 </weight>
#<weight id="8538"> lhapdf=90238 </weight>
#<weight id="8539"> lhapdf=90239 </weight>
#<weight id="8540"> lhapdf=90240 </weight>
#<weight id="8541"> lhapdf=90241 </weight>
#<weight id="8542"> lhapdf=90242 </weight>
#<weight id="8543"> lhapdf=90243 </weight>
#<weight id="8544"> lhapdf=90244 </weight>
#<weight id="8545"> lhapdf=90245 </weight>
#<weight id="8546"> lhapdf=90246 </weight>
#<weight id="8547"> lhapdf=90247 </weight>
#<weight id="8548"> lhapdf=90248 </weight>
#<weight id="8549"> lhapdf=90249 </weight>
#<weight id="8550"> lhapdf=90250 </weight>
#<weight id="8551"> lhapdf=90251 </weight>
#<weight id="8552"> lhapdf=90252 </weight>
#<weight id="8553"> lhapdf=90253 </weight>
#<weight id="8554"> lhapdf=90254 </weight>
#<weight id="8555"> lhapdf=90255 </weight>
#<weight id="8556"> lhapdf=90256 </weight>
#<weight id="8557"> lhapdf=90257 </weight>
#<weight id="8558"> lhapdf=90258 </weight>
#<weight id="8559"> lhapdf=90259 </weight>
#<weight id="8560"> lhapdf=90260 </weight>
#<weight id="8561"> lhapdf=90261 </weight>
#<weight id="8562"> lhapdf=90262 </weight>
#<weight id="8563"> lhapdf=90263 </weight>
#<weight id="8564"> lhapdf=90264 </weight>
#<weight id="8565"> lhapdf=90265 </weight>
#<weight id="8566"> lhapdf=90266 </weight>
#<weight id="8567"> lhapdf=90267 </weight>
#<weight id="8568"> lhapdf=90268 </weight>
#<weight id="8569"> lhapdf=90269 </weight>
#<weight id="8570"> lhapdf=90270 </weight>
#<weight id="8571"> lhapdf=90271 </weight>
#<weight id="8572"> lhapdf=90272 </weight>
#<weight id="8573"> lhapdf=90273 </weight>
#<weight id="8574"> lhapdf=90274 </weight>
#<weight id="8575"> lhapdf=90275 </weight>
#<weight id="8576"> lhapdf=90276 </weight>
#<weight id="8577"> lhapdf=90277 </weight>
#<weight id="8578"> lhapdf=90278 </weight>
#<weight id="8579"> lhapdf=90279 </weight>
#<weight id="8580"> lhapdf=90280 </weight>
#<weight id="8581"> lhapdf=90281 </weight>
#<weight id="8582"> lhapdf=90282 </weight>
#<weight id="8583"> lhapdf=90283 </weight>
#<weight id="8584"> lhapdf=90284 </weight>
#<weight id="8585"> lhapdf=90285 </weight>
#<weight id="8586"> lhapdf=90286 </weight>
#<weight id="8587"> lhapdf=90287 </weight>
#<weight id="8588"> lhapdf=90288 </weight>
#<weight id="8589"> lhapdf=90289 </weight>
#<weight id="8590"> lhapdf=90290 </weight>
#<weight id="8591"> lhapdf=90291 </weight>
#<weight id="8592"> lhapdf=90292 </weight>
#<weight id="8593"> lhapdf=90293 </weight>
#<weight id="8594"> lhapdf=90294 </weight>
#<weight id="8595"> lhapdf=90295 </weight>
#<weight id="8596"> lhapdf=90296 </weight>
#<weight id="8597"> lhapdf=90297 </weight>
#<weight id="8598"> lhapdf=90298 </weight>
#<weight id="8599"> lhapdf=90299 </weight>
#<weight id="8600"> lhapdf=90300 </weight>
#<weight id="8601"> lhapdf=90301 </weight>
#<weight id="8602"> lhapdf=90302 </weight>
#<weight id="9000"> lhapdf=91200 </weight>
#<weight id="9001"> lhapdf=91201 </weight>
#<weight id="9002"> lhapdf=91202 </weight>
#<weight id="9003"> lhapdf=91203 </weight>
#<weight id="9004"> lhapdf=91204 </weight>
#<weight id="9005"> lhapdf=91205 </weight>
#<weight id="9006"> lhapdf=91206 </weight>
#<weight id="9007"> lhapdf=91207 </weight>
#<weight id="9008"> lhapdf=91208 </weight>
#<weight id="9009"> lhapdf=91209 </weight>
#<weight id="9010"> lhapdf=91210 </weight>
#<weight id="9011"> lhapdf=91211 </weight>
#<weight id="9012"> lhapdf=91212 </weight>
#<weight id="9013"> lhapdf=91213 </weight>
#<weight id="9014"> lhapdf=91214 </weight>
#<weight id="9015"> lhapdf=91215 </weight>
#<weight id="9016"> lhapdf=91216 </weight>
#<weight id="9017"> lhapdf=91217 </weight>
#<weight id="9018"> lhapdf=91218 </weight>
#<weight id="9019"> lhapdf=91219 </weight>
#<weight id="9020"> lhapdf=91220 </weight>
#<weight id="9021"> lhapdf=91221 </weight>
#<weight id="9022"> lhapdf=91222 </weight>
#<weight id="9023"> lhapdf=91223 </weight>
#<weight id="9024"> lhapdf=91224 </weight>
#<weight id="9025"> lhapdf=91225 </weight>
#<weight id="9026"> lhapdf=91226 </weight>
#<weight id="9027"> lhapdf=91227 </weight>
#<weight id="9028"> lhapdf=91228 </weight>
#<weight id="9029"> lhapdf=91229 </weight>
#<weight id="9030"> lhapdf=91230 </weight>
#<weight id="9031"> lhapdf=91231 </weight>
#<weight id="9032"> lhapdf=91232 </weight>
#<weight id="9033"> lhapdf=91233 </weight>
#<weight id="9034"> lhapdf=91234 </weight>
#<weight id="9035"> lhapdf=91235 </weight>
#<weight id="9036"> lhapdf=91236 </weight>
#<weight id="9037"> lhapdf=91237 </weight>
#<weight id="9038"> lhapdf=91238 </weight>
#<weight id="9039"> lhapdf=91239 </weight>
#<weight id="9040"> lhapdf=91240 </weight>
#<weight id="9041"> lhapdf=91241 </weight>
#<weight id="9042"> lhapdf=91242 </weight>
#<weight id="9043"> lhapdf=91243 </weight>
#<weight id="9044"> lhapdf=91244 </weight>
#<weight id="9045"> lhapdf=91245 </weight>
#<weight id="9046"> lhapdf=91246 </weight>
#<weight id="9047"> lhapdf=91247 </weight>
#<weight id="9048"> lhapdf=91248 </weight>
#<weight id="9049"> lhapdf=91249 </weight>
#<weight id="9050"> lhapdf=91250 </weight>
#<weight id="9051"> lhapdf=91251 </weight>
#<weight id="9052"> lhapdf=91252 </weight>
#<weight id="9053"> lhapdf=91253 </weight>
#<weight id="9054"> lhapdf=91254 </weight>
#<weight id="9055"> lhapdf=91255 </weight>
#<weight id="9056"> lhapdf=91256 </weight>
#<weight id="9057"> lhapdf=91257 </weight>
#<weight id="9058"> lhapdf=91258 </weight>
#<weight id="9059"> lhapdf=91259 </weight>
#<weight id="9060"> lhapdf=91260 </weight>
#<weight id="9061"> lhapdf=91261 </weight>
#<weight id="9062"> lhapdf=91262 </weight>
#<weight id="9063"> lhapdf=91263 </weight>
#<weight id="9064"> lhapdf=91264 </weight>
#<weight id="9065"> lhapdf=91265 </weight>
#<weight id="9066"> lhapdf=91266 </weight>
#<weight id="9067"> lhapdf=91267 </weight>
#<weight id="9068"> lhapdf=91268 </weight>
#<weight id="9069"> lhapdf=91269 </weight>
#<weight id="9070"> lhapdf=91270 </weight>
#<weight id="9071"> lhapdf=91271 </weight>
#<weight id="9072"> lhapdf=91272 </weight>
#<weight id="9073"> lhapdf=91273 </weight>
#<weight id="9074"> lhapdf=91274 </weight>
#<weight id="9075"> lhapdf=91275 </weight>
#<weight id="9076"> lhapdf=91276 </weight>
#<weight id="9077"> lhapdf=91277 </weight>
#<weight id="9078"> lhapdf=91278 </weight>
#<weight id="9079"> lhapdf=91279 </weight>
#<weight id="9080"> lhapdf=91280 </weight>
#<weight id="9081"> lhapdf=91281 </weight>
#<weight id="9082"> lhapdf=91282 </weight>
#<weight id="9083"> lhapdf=91283 </weight>
#<weight id="9084"> lhapdf=91284 </weight>
#<weight id="9085"> lhapdf=91285 </weight>
#<weight id="9086"> lhapdf=91286 </weight>
#<weight id="9087"> lhapdf=91287 </weight>
#<weight id="9088"> lhapdf=91288 </weight>
#<weight id="9089"> lhapdf=91289 </weight>
#<weight id="9090"> lhapdf=91290 </weight>
#<weight id="9091"> lhapdf=91291 </weight>
#<weight id="9092"> lhapdf=91292 </weight>
#<weight id="9093"> lhapdf=91293 </weight>
#<weight id="9094"> lhapdf=91294 </weight>
#<weight id="9095"> lhapdf=91295 </weight>
#<weight id="9096"> lhapdf=91296 </weight>
#<weight id="9097"> lhapdf=91297 </weight>
#<weight id="9098"> lhapdf=91298 </weight>
#<weight id="9099"> lhapdf=91299 </weight>
#<weight id="9100"> lhapdf=91300 </weight>
#<weight id="9101"> lhapdf=91301 </weight>
#<weight id="9102"> lhapdf=91302 </weight>
#<weight id="10000"> lhapdf=90400 </weight>
#<weight id="10001"> lhapdf=90401 </weight>
#<weight id="10002"> lhapdf=90402 </weight>
#<weight id="10003"> lhapdf=90403 </weight>
#<weight id="10004"> lhapdf=90404 </weight>
#<weight id="10005"> lhapdf=90405 </weight>
#<weight id="10006"> lhapdf=90406 </weight>
#<weight id="10007"> lhapdf=90407 </weight>
#<weight id="10008"> lhapdf=90408 </weight>
#<weight id="10009"> lhapdf=90409 </weight>
#<weight id="10010"> lhapdf=90410 </weight>
#<weight id="10011"> lhapdf=90411 </weight>
#<weight id="10012"> lhapdf=90412 </weight>
#<weight id="10013"> lhapdf=90413 </weight>
#<weight id="10014"> lhapdf=90414 </weight>
#<weight id="10015"> lhapdf=90415 </weight>
#<weight id="10016"> lhapdf=90416 </weight>
#<weight id="10017"> lhapdf=90417 </weight>
#<weight id="10018"> lhapdf=90418 </weight>
#<weight id="10019"> lhapdf=90419 </weight>
#<weight id="10020"> lhapdf=90420 </weight>
#<weight id="10021"> lhapdf=90421 </weight>
#<weight id="10022"> lhapdf=90422 </weight>
#<weight id="10023"> lhapdf=90423 </weight>
#<weight id="10024"> lhapdf=90424 </weight>
#<weight id="10025"> lhapdf=90425 </weight>
#<weight id="10026"> lhapdf=90426 </weight>
#<weight id="10027"> lhapdf=90427 </weight>
#<weight id="10028"> lhapdf=90428 </weight>
#<weight id="10029"> lhapdf=90429 </weight>
#<weight id="10030"> lhapdf=90430 </weight>
#<weight id="10031"> lhapdf=90431 </weight>
#<weight id="10032"> lhapdf=90432 </weight>
#<weight id="11000"> lhapdf=91400 </weight>
#<weight id="11001"> lhapdf=91401 </weight>
#<weight id="11002"> lhapdf=91402 </weight>
#<weight id="11003"> lhapdf=91403 </weight>
#<weight id="11004"> lhapdf=91404 </weight>
#<weight id="11005"> lhapdf=91405 </weight>
#<weight id="11006"> lhapdf=91406 </weight>
#<weight id="11007"> lhapdf=91407 </weight>
#<weight id="11008"> lhapdf=91408 </weight>
#<weight id="11009"> lhapdf=91409 </weight>
#<weight id="11010"> lhapdf=91410 </weight>
#<weight id="11011"> lhapdf=91411 </weight>
#<weight id="11012"> lhapdf=91412 </weight>
#<weight id="11013"> lhapdf=91413 </weight>
#<weight id="11014"> lhapdf=91414 </weight>
#<weight id="11015"> lhapdf=91415 </weight>
#<weight id="11016"> lhapdf=91416 </weight>
#<weight id="11017"> lhapdf=91417 </weight>
#<weight id="11018"> lhapdf=91418 </weight>
#<weight id="11019"> lhapdf=91419 </weight>
#<weight id="11020"> lhapdf=91420 </weight>
#<weight id="11021"> lhapdf=91421 </weight>
#<weight id="11022"> lhapdf=91422 </weight>
#<weight id="11023"> lhapdf=91423 </weight>
#<weight id="11024"> lhapdf=91424 </weight>
#<weight id="11025"> lhapdf=91425 </weight>
#<weight id="11026"> lhapdf=91426 </weight>
#<weight id="11027"> lhapdf=91427 </weight>
#<weight id="11028"> lhapdf=91428 </weight>
#<weight id="11029"> lhapdf=91429 </weight>
#<weight id="11030"> lhapdf=91430 </weight>
#<weight id="11031"> lhapdf=91431 </weight>
#<weight id="11032"> lhapdf=91432 </weight>
#<weight id="12000"> lhapdf=61100 </weight>
#<weight id="12001"> lhapdf=61101 </weight>
#<weight id="12002"> lhapdf=61102 </weight>
#<weight id="12003"> lhapdf=61103 </weight>
#<weight id="12004"> lhapdf=61104 </weight>
#<weight id="12005"> lhapdf=61105 </weight>
#<weight id="12006"> lhapdf=61106 </weight>
#<weight id="12007"> lhapdf=61107 </weight>
#<weight id="12008"> lhapdf=61108 </weight>
#<weight id="12009"> lhapdf=61109 </weight>
#<weight id="12010"> lhapdf=61110 </weight>
#<weight id="12011"> lhapdf=61111 </weight>
#<weight id="12012"> lhapdf=61112 </weight>
#<weight id="12013"> lhapdf=61113 </weight>
#<weight id="12014"> lhapdf=61114 </weight>
#<weight id="12015"> lhapdf=61115 </weight>
#<weight id="12016"> lhapdf=61116 </weight>
#<weight id="12017"> lhapdf=61117 </weight>
#<weight id="12018"> lhapdf=61118 </weight>
#<weight id="12019"> lhapdf=61119 </weight>
#<weight id="12020"> lhapdf=61120 </weight>
#<weight id="12021"> lhapdf=61121 </weight>
#<weight id="12022"> lhapdf=61122 </weight>
#<weight id="12023"> lhapdf=61123 </weight>
#<weight id="12024"> lhapdf=61124 </weight>
#<weight id="12025"> lhapdf=61125 </weight>
#<weight id="12026"> lhapdf=61126 </weight>
#<weight id="12027"> lhapdf=61127 </weight>
#<weight id="12028"> lhapdf=61128 </weight>
#<weight id="12050"> lhapdf=61130 </weight>
#<weight id="12051"> lhapdf=61131 </weight>
#<weight id="12052"> lhapdf=61132 </weight>
#<weight id="12053"> lhapdf=61133 </weight>
#<weight id="12054"> lhapdf=61134 </weight>
#<weight id="12055"> lhapdf=61135 </weight>
#<weight id="12056"> lhapdf=61136 </weight>
#<weight id="12057"> lhapdf=61137 </weight>
#<weight id="12058"> lhapdf=61138 </weight>
#<weight id="12059"> lhapdf=61139 </weight>
#<weight id="12060"> lhapdf=61140 </weight>
#<weight id="12061"> lhapdf=61141 </weight>
#<weight id="12062"> lhapdf=61142 </weight>
#<weight id="12063"> lhapdf=61143 </weight>
#<weight id="13000"> lhapdf=61200 </weight>
#<weight id="13001"> lhapdf=61201 </weight>
#<weight id="13002"> lhapdf=61202 </weight>
#<weight id="13003"> lhapdf=61203 </weight>
#<weight id="13004"> lhapdf=61204 </weight>
#<weight id="13005"> lhapdf=61205 </weight>
#<weight id="13006"> lhapdf=61206 </weight>
#<weight id="13007"> lhapdf=61207 </weight>
#<weight id="13008"> lhapdf=61208 </weight>
#<weight id="13009"> lhapdf=61209 </weight>
#<weight id="13010"> lhapdf=61210 </weight>
#<weight id="13011"> lhapdf=61211 </weight>
#<weight id="13012"> lhapdf=61212 </weight>
#<weight id="13013"> lhapdf=61213 </weight>
#<weight id="13014"> lhapdf=61214 </weight>
#<weight id="13015"> lhapdf=61215 </weight>
#<weight id="13016"> lhapdf=61216 </weight>
#<weight id="13017"> lhapdf=61217 </weight>
#<weight id="13018"> lhapdf=61218 </weight>
#<weight id="13019"> lhapdf=61219 </weight>
#<weight id="13020"> lhapdf=61220 </weight>
#<weight id="13021"> lhapdf=61221 </weight>
#<weight id="13022"> lhapdf=61222 </weight>
#<weight id="13023"> lhapdf=61223 </weight>
#<weight id="13024"> lhapdf=61224 </weight>
#<weight id="13025"> lhapdf=61225 </weight>
#<weight id="13026"> lhapdf=61226 </weight>
#<weight id="13027"> lhapdf=61227 </weight>
#<weight id="13028"> lhapdf=61228 </weight>
#<weight id="13050"> lhapdf=61230 </weight>
#<weight id="13051"> lhapdf=61231 </weight>
#<weight id="13052"> lhapdf=61232 </weight>
#<weight id="13053"> lhapdf=61233 </weight>
#<weight id="13054"> lhapdf=61234 </weight>
#<weight id="13055"> lhapdf=61235 </weight>
#<weight id="13056"> lhapdf=61236 </weight>
#<weight id="13057"> lhapdf=61237 </weight>
#<weight id="13058"> lhapdf=61238 </weight>
#<weight id="13059"> lhapdf=61239 </weight>
#<weight id="13060"> lhapdf=61240 </weight>
#<weight id="13061"> lhapdf=61241 </weight>
#<weight id="13062"> lhapdf=61242 </weight>
#<weight id="13063"> lhapdf=61243 </weight>
#<weight id="14000"> lhapdf=13400 </weight>
#<weight id="14001"> lhapdf=13401 </weight>
#<weight id="14002"> lhapdf=13402 </weight>
#<weight id="14003"> lhapdf=13403 </weight>
#<weight id="14004"> lhapdf=13404 </weight>
#<weight id="14005"> lhapdf=13405 </weight>
#<weight id="14006"> lhapdf=13406 </weight>
#<weight id="14007"> lhapdf=13407 </weight>
#<weight id="14008"> lhapdf=13408 </weight>
#<weight id="14009"> lhapdf=13409 </weight>
#<weight id="14010"> lhapdf=13410 </weight>
#<weight id="14011"> lhapdf=13411 </weight>
#<weight id="14012"> lhapdf=13412 </weight>
#<weight id="14013"> lhapdf=13413 </weight>
#<weight id="14014"> lhapdf=13414 </weight>
#<weight id="14015"> lhapdf=13415 </weight>
#<weight id="14016"> lhapdf=13416 </weight>
#<weight id="14017"> lhapdf=13417 </weight>
#<weight id="14018"> lhapdf=13418 </weight>
#<weight id="14019"> lhapdf=13419 </weight>
#<weight id="14020"> lhapdf=13420 </weight>
#<weight id="14021"> lhapdf=13421 </weight>
#<weight id="14022"> lhapdf=13422 </weight>
#<weight id="14023"> lhapdf=13423 </weight>
#<weight id="14024"> lhapdf=13424 </weight>
#<weight id="14025"> lhapdf=13425 </weight>
#<weight id="14026"> lhapdf=13426 </weight>
#<weight id="14027"> lhapdf=13427 </weight>
#<weight id="14028"> lhapdf=13428 </weight>
#<weight id="14029"> lhapdf=13429 </weight>
#<weight id="14030"> lhapdf=13430 </weight>
#<weight id="15000"> lhapdf=82200 </weight>
#<weight id="15001"> lhapdf=82201 </weight>
#<weight id="15002"> lhapdf=82202 </weight>
#<weight id="15003"> lhapdf=82203 </weight>
#<weight id="15004"> lhapdf=82204 </weight>
#<weight id="15005"> lhapdf=82205 </weight>
#<weight id="15006"> lhapdf=82206 </weight>
#<weight id="15007"> lhapdf=82207 </weight>
#<weight id="15008"> lhapdf=82208 </weight>
#<weight id="15009"> lhapdf=82209 </weight>
#<weight id="15010"> lhapdf=82210 </weight>
#<weight id="15011"> lhapdf=82211 </weight>
#<weight id="15012"> lhapdf=82212 </weight>
#<weight id="15013"> lhapdf=82213 </weight>
#<weight id="15014"> lhapdf=82214 </weight>
#<weight id="15015"> lhapdf=82215 </weight>
#<weight id="15016"> lhapdf=82216 </weight>
#<weight id="15017"> lhapdf=82217 </weight>
#<weight id="15018"> lhapdf=82218 </weight>
#<weight id="15019"> lhapdf=82219 </weight>
#<weight id="15020"> lhapdf=82220 </weight>
#<weight id="15021"> lhapdf=82221 </weight>
#<weight id="15022"> lhapdf=82222 </weight>
#<weight id="15023"> lhapdf=82223 </weight>
#<weight id="15024"> lhapdf=82224 </weight>
#<weight id="15025"> lhapdf=82225 </weight>
#<weight id="15026"> lhapdf=82226 </weight>
#<weight id="15027"> lhapdf=82227 </weight>
#<weight id="15028"> lhapdf=82228 </weight>
#<weight id="15029"> lhapdf=82229 </weight>
#<weight id="15030"> lhapdf=82230 </weight>
#<weight id="15031"> lhapdf=82231 </weight>
#<weight id="15032"> lhapdf=82232 </weight>
#<weight id="15033"> lhapdf=82233 </weight>
#<weight id="15034"> lhapdf=82234 </weight>
#<weight id="15035"> lhapdf=82235 </weight>
#<weight id="15036"> lhapdf=82236 </weight>
#<weight id="15037"> lhapdf=82237 </weight>
#<weight id="15038"> lhapdf=82238 </weight>
#<weight id="15039"> lhapdf=82239 </weight>
#<weight id="15040"> lhapdf=82240 </weight>
#<weight id="15041"> lhapdf=82241 </weight>
#<weight id="15042"> lhapdf=82242 </weight>
#<weight id="15043"> lhapdf=82243 </weight>
#<weight id="15044"> lhapdf=82244 </weight>
#<weight id="15045"> lhapdf=82245 </weight>
#<weight id="15046"> lhapdf=82246 </weight>
#<weight id="15047"> lhapdf=82247 </weight>
#<weight id="15048"> lhapdf=82248 </weight>
#<weight id="15049"> lhapdf=82249 </weight>
#<weight id="15050"> lhapdf=82250 </weight>
#<weight id="15051"> lhapdf=82251 </weight>
#<weight id="15052"> lhapdf=82252 </weight>
#<weight id="15053"> lhapdf=82253 </weight>
#<weight id="15054"> lhapdf=82254 </weight>
#<weight id="15055"> lhapdf=82255 </weight>
#<weight id="15056"> lhapdf=82256 </weight>
#<weight id="15057"> lhapdf=82257 </weight>
#<weight id="15058"> lhapdf=82258 </weight>
#<weight id="15059"> lhapdf=82259 </weight>
#<weight id="15060"> lhapdf=82260 </weight>
#<weight id="15061"> lhapdf=82261 </weight>
#<weight id="15062"> lhapdf=82262 </weight>
#<weight id="15063"> lhapdf=82263 </weight>
#<weight id="15064"> lhapdf=82264 </weight>
#<weight id="15065"> lhapdf=82265 </weight>
#<weight id="15066"> lhapdf=82266 </weight>
#<weight id="15067"> lhapdf=82267 </weight>
#<weight id="15068"> lhapdf=82268 </weight>
#<weight id="15069"> lhapdf=82269 </weight>
#<weight id="15070"> lhapdf=82270 </weight>
#<weight id="15071"> lhapdf=82271 </weight>
#<weight id="15072"> lhapdf=82272 </weight>
#<weight id="15073"> lhapdf=82273 </weight>
#<weight id="15074"> lhapdf=82274 </weight>
#<weight id="15075"> lhapdf=82275 </weight>
#<weight id="15076"> lhapdf=82276 </weight>
#<weight id="15077"> lhapdf=82277 </weight>
#<weight id="15078"> lhapdf=82278 </weight>
#<weight id="15079"> lhapdf=82279 </weight>
#<weight id="15080"> lhapdf=82280 </weight>
#<weight id="15081"> lhapdf=82281 </weight>
#<weight id="15082"> lhapdf=82282 </weight>
#<weight id="15083"> lhapdf=82283 </weight>
#<weight id="15084"> lhapdf=82284 </weight>
#<weight id="15085"> lhapdf=82285 </weight>
#<weight id="15086"> lhapdf=82286 </weight>
#<weight id="15087"> lhapdf=82287 </weight>
#<weight id="15088"> lhapdf=82288 </weight>
#<weight id="15089"> lhapdf=82289 </weight>
#<weight id="15090"> lhapdf=82290 </weight>
#<weight id="15091"> lhapdf=82291 </weight>
#<weight id="15092"> lhapdf=82292 </weight>
#<weight id="15093"> lhapdf=82293 </weight>
#<weight id="15094"> lhapdf=82294 </weight>
#<weight id="15095"> lhapdf=82295 </weight>
#<weight id="15096"> lhapdf=82296 </weight>
#<weight id="15097"> lhapdf=82297 </weight>
#<weight id="15098"> lhapdf=82298 </weight>
#<weight id="15099"> lhapdf=82299 </weight>
#<weight id="15100"> lhapdf=82300 </weight>
#<weight id="15101"> lhapdf=82301 </weight>
#<weight id="15102"> lhapdf=82302 </weight>
#<weight id="15103"> lhapdf=82303 </weight>
#<weight id="15104"> lhapdf=82304 </weight>
#<weight id="15105"> lhapdf=82305 </weight>
#<weight id="15106"> lhapdf=82306 </weight>
#<weight id="15107"> lhapdf=82307 </weight>





##TT 2018
#weightgroup combine="hessian" name="PDF_variation1">
#<weight id="2000"> lhapdf=306000 </weight>
#<weight id="2001"> lhapdf=306001 </weight>
#<weight id="2002"> lhapdf=306002 </weight>
#<weight id="2003"> lhapdf=306003 </weight>
#<weight id="2004"> lhapdf=306004 </weight>
#<weight id="2005"> lhapdf=306005 </weight>
#<weight id="2006"> lhapdf=306006 </weight>
#<weight id="2007"> lhapdf=306007 </weight>
#<weight id="2008"> lhapdf=306008 </weight>
#<weight id="2009"> lhapdf=306009 </weight>
#<weight id="2010"> lhapdf=306010 </weight>
#<weight id="2011"> lhapdf=306011 </weight>
#<weight id="2012"> lhapdf=306012 </weight>
#<weight id="2013"> lhapdf=306013 </weight>
#<weight id="2014"> lhapdf=306014 </weight>
#<weight id="2015"> lhapdf=306015 </weight>
#<weight id="2016"> lhapdf=306016 </weight>
#<weight id="2017"> lhapdf=306017 </weight>
#<weight id="2018"> lhapdf=306018 </weight>
#<weight id="2019"> lhapdf=306019 </weight>
#<weight id="2020"> lhapdf=306020 </weight>
#<weight id="2021"> lhapdf=306021 </weight>
#<weight id="2022"> lhapdf=306022 </weight>
#<weight id="2023"> lhapdf=306023 </weight>
#<weight id="2024"> lhapdf=306024 </weight>
#<weight id="2025"> lhapdf=306025 </weight>
#<weight id="2026"> lhapdf=306026 </weight>
#<weight id="2027"> lhapdf=306027 </weight>
#<weight id="2028"> lhapdf=306028 </weight>
#<weight id="2029"> lhapdf=306029 </weight>
#<weight id="2030"> lhapdf=306030 </weight>
#<weight id="2031"> lhapdf=306031 </weight>
#<weight id="2032"> lhapdf=306032 </weight>
#<weight id="2033"> lhapdf=306033 </weight>
#<weight id="2034"> lhapdf=306034 </weight>
#<weight id="2035"> lhapdf=306035 </weight>
#<weight id="2036"> lhapdf=306036 </weight>
#<weight id="2037"> lhapdf=306037 </weight>
#<weight id="2038"> lhapdf=306038 </weight>
#<weight id="2039"> lhapdf=306039 </weight>
#<weight id="2040"> lhapdf=306040 </weight>
#<weight id="2041"> lhapdf=306041 </weight>
#<weight id="2042"> lhapdf=306042 </weight>
#<weight id="2043"> lhapdf=306043 </weight>
#<weight id="2044"> lhapdf=306044 </weight>
#<weight id="2045"> lhapdf=306045 </weight>
#<weight id="2046"> lhapdf=306046 </weight>
#<weight id="2047"> lhapdf=306047 </weight>
#<weight id="2048"> lhapdf=306048 </weight>
#<weight id="2049"> lhapdf=306049 </weight>
#<weight id="2050"> lhapdf=306050 </weight>
#<weight id="2051"> lhapdf=306051 </weight>
#<weight id="2052"> lhapdf=306052 </weight>
#<weight id="2053"> lhapdf=306053 </weight>
#<weight id="2054"> lhapdf=306054 </weight>
#<weight id="2055"> lhapdf=306055 </weight>
#<weight id="2056"> lhapdf=306056 </weight>
#<weight id="2057"> lhapdf=306057 </weight>
#<weight id="2058"> lhapdf=306058 </weight>
#<weight id="2059"> lhapdf=306059 </weight>
#<weight id="2060"> lhapdf=306060 </weight>
#<weight id="2061"> lhapdf=306061 </weight>
#<weight id="2062"> lhapdf=306062 </weight>
#<weight id="2063"> lhapdf=306063 </weight>
#<weight id="2064"> lhapdf=306064 </weight>
#<weight id="2065"> lhapdf=306065 </weight>
#<weight id="2066"> lhapdf=306066 </weight>
#<weight id="2067"> lhapdf=306067 </weight>
#<weight id="2068"> lhapdf=306068 </weight>
#<weight id="2069"> lhapdf=306069 </weight>
#<weight id="2070"> lhapdf=306070 </weight>
#<weight id="2071"> lhapdf=306071 </weight>
#<weight id="2072"> lhapdf=306072 </weight>
#<weight id="2073"> lhapdf=306073 </weight>
#<weight id="2074"> lhapdf=306074 </weight>
#<weight id="2075"> lhapdf=306075 </weight>
#<weight id="2076"> lhapdf=306076 </weight>
#<weight id="2077"> lhapdf=306077 </weight>
#<weight id="2078"> lhapdf=306078 </weight>
#<weight id="2079"> lhapdf=306079 </weight>
#<weight id="2080"> lhapdf=306080 </weight>
#<weight id="2081"> lhapdf=306081 </weight>
#<weight id="2082"> lhapdf=306082 </weight>
#<weight id="2083"> lhapdf=306083 </weight>
#<weight id="2084"> lhapdf=306084 </weight>
#<weight id="2085"> lhapdf=306085 </weight>
#<weight id="2086"> lhapdf=306086 </weight>
#<weight id="2087"> lhapdf=306087 </weight>
#<weight id="2088"> lhapdf=306088 </weight>
#<weight id="2089"> lhapdf=306089 </weight>
#<weight id="2090"> lhapdf=306090 </weight>
#<weight id="2091"> lhapdf=306091 </weight>
#<weight id="2092"> lhapdf=306092 </weight>
#<weight id="2093"> lhapdf=306093 </weight>
#<weight id="2094"> lhapdf=306094 </weight>
#<weight id="2095"> lhapdf=306095 </weight>
#<weight id="2096"> lhapdf=306096 </weight>
#<weight id="2097"> lhapdf=306097 </weight>
#<weight id="2098"> lhapdf=306098 </weight>
#<weight id="2099"> lhapdf=306099 </weight>
#<weight id="2100"> lhapdf=306100 </weight>
#<weight id="2101"> lhapdf=306101 </weight>
#<weight id="2102"> lhapdf=306102 </weight>
#<weight id="2104"> lhapdf=322500 </weight>
#<weight id="2105"> lhapdf=322700 </weight>
#<weight id="2106"> lhapdf=322900 </weight>
#<weight id="2107"> lhapdf=323100 </weight>
#<weight id="2108"> lhapdf=323300 </weight>
#<weight id="2109"> lhapdf=323500 </weight>
#<weight id="2110"> lhapdf=323700 </weight>
#<weight id="2111"> lhapdf=323900 </weight>
#<weight id="3000"> lhapdf=305800 </weight>
#<weight id="3001"> lhapdf=305801 </weight>
#<weight id="3002"> lhapdf=305802 </weight>
#<weight id="3003"> lhapdf=305803 </weight>
#<weight id="3004"> lhapdf=305804 </weight>
#<weight id="3005"> lhapdf=305805 </weight>
#<weight id="3006"> lhapdf=305806 </weight>
#<weight id="3007"> lhapdf=305807 </weight>
#<weight id="3008"> lhapdf=305808 </weight>
#<weight id="3009"> lhapdf=305809 </weight>
#<weight id="3010"> lhapdf=305810 </weight>
#<weight id="3011"> lhapdf=305811 </weight>
#<weight id="3012"> lhapdf=305812 </weight>
#<weight id="3013"> lhapdf=305813 </weight>
#<weight id="3014"> lhapdf=305814 </weight>
#<weight id="3015"> lhapdf=305815 </weight>
#<weight id="3016"> lhapdf=305816 </weight>
#<weight id="3017"> lhapdf=305817 </weight>
#<weight id="3018"> lhapdf=305818 </weight>
#<weight id="3019"> lhapdf=305819 </weight>
#<weight id="3020"> lhapdf=305820 </weight>
#<weight id="3021"> lhapdf=305821 </weight>
#<weight id="3022"> lhapdf=305822 </weight>
#<weight id="3023"> lhapdf=305823 </weight>
#<weight id="3024"> lhapdf=305824 </weight>
#<weight id="3025"> lhapdf=305825 </weight>
#<weight id="3026"> lhapdf=305826 </weight>
#<weight id="3027"> lhapdf=305827 </weight>
#<weight id="3028"> lhapdf=305828 </weight>
#<weight id="3029"> lhapdf=305829 </weight>
#<weight id="3030"> lhapdf=305830 </weight>
#<weight id="3031"> lhapdf=305831 </weight>
#<weight id="3032"> lhapdf=305832 </weight>
#<weight id="3033"> lhapdf=305833 </weight>
#<weight id="3034"> lhapdf=305834 </weight>
#<weight id="3035"> lhapdf=305835 </weight>
#<weight id="3036"> lhapdf=305836 </weight>
#<weight id="3037"> lhapdf=305837 </weight>
#<weight id="3038"> lhapdf=305838 </weight>
#<weight id="3039"> lhapdf=305839 </weight>
#<weight id="3040"> lhapdf=305840 </weight>
#<weight id="3041"> lhapdf=305841 </weight>
#<weight id="3042"> lhapdf=305842 </weight>
#<weight id="3043"> lhapdf=305843 </weight>
#<weight id="3044"> lhapdf=305844 </weight>
#<weight id="3045"> lhapdf=305845 </weight>
#<weight id="3046"> lhapdf=305846 </weight>
#<weight id="3047"> lhapdf=305847 </weight>
#<weight id="3048"> lhapdf=305848 </weight>
#<weight id="3049"> lhapdf=305849 </weight>
#<weight id="3050"> lhapdf=305850 </weight>
#<weight id="3051"> lhapdf=305851 </weight>
#<weight id="3052"> lhapdf=305852 </weight>
#<weight id="3053"> lhapdf=305853 </weight>
#<weight id="3054"> lhapdf=305854 </weight>
#<weight id="3055"> lhapdf=305855 </weight>
#<weight id="3056"> lhapdf=305856 </weight>
#<weight id="3057"> lhapdf=305857 </weight>
#<weight id="3058"> lhapdf=305858 </weight>
#<weight id="3059"> lhapdf=305859 </weight>
#<weight id="3060"> lhapdf=305860 </weight>
#<weight id="3061"> lhapdf=305861 </weight>
#<weight id="3062"> lhapdf=305862 </weight>
#<weight id="3063"> lhapdf=305863 </weight>
#<weight id="3064"> lhapdf=305864 </weight>
#<weight id="3065"> lhapdf=305865 </weight>
#<weight id="3066"> lhapdf=305866 </weight>
#<weight id="3067"> lhapdf=305867 </weight>
#<weight id="3068"> lhapdf=305868 </weight>
#<weight id="3069"> lhapdf=305869 </weight>
#<weight id="3070"> lhapdf=305870 </weight>
#<weight id="3071"> lhapdf=305871 </weight>
#<weight id="3072"> lhapdf=305872 </weight>
#<weight id="3073"> lhapdf=305873 </weight>
#<weight id="3074"> lhapdf=305874 </weight>
#<weight id="3075"> lhapdf=305875 </weight>
#<weight id="3076"> lhapdf=305876 </weight>
#<weight id="3077"> lhapdf=305877 </weight>
#<weight id="3078"> lhapdf=305878 </weight>
#<weight id="3079"> lhapdf=305879 </weight>
#<weight id="3080"> lhapdf=305880 </weight>
#<weight id="3081"> lhapdf=305881 </weight>
#<weight id="3082"> lhapdf=305882 </weight>
#<weight id="3083"> lhapdf=305883 </weight>
#<weight id="3084"> lhapdf=305884 </weight>
#<weight id="3085"> lhapdf=305885 </weight>
#<weight id="3086"> lhapdf=305886 </weight>
#<weight id="3087"> lhapdf=305887 </weight>
#<weight id="3088"> lhapdf=305888 </weight>
#<weight id="3089"> lhapdf=305889 </weight>
#<weight id="3090"> lhapdf=305890 </weight>
#<weight id="3091"> lhapdf=305891 </weight>
#<weight id="3092"> lhapdf=305892 </weight>
#<weight id="3093"> lhapdf=305893 </weight>
#<weight id="3094"> lhapdf=305894 </weight>
#<weight id="3095"> lhapdf=305895 </weight>
#<weight id="3096"> lhapdf=305896 </weight>
#<weight id="3097"> lhapdf=305897 </weight>
#<weight id="3098"> lhapdf=305898 </weight>
#<weight id="3099"> lhapdf=305899 </weight>
#<weight id="3100"> lhapdf=305900 </weight>
#<weight id="3101"> lhapdf=305901 </weight>
#<weight id="3102"> lhapdf=305902 </weight>
#<weight id="5000"> lhapdf=13000 </weight>
#<weight id="5001"> lhapdf=13001 </weight>
#<weight id="5002"> lhapdf=13002 </weight>
#<weight id="5003"> lhapdf=13003 </weight>
#<weight id="5004"> lhapdf=13004 </weight>
#<weight id="5005"> lhapdf=13005 </weight>
#<weight id="5006"> lhapdf=13006 </weight>
#<weight id="5007"> lhapdf=13007 </weight>
#<weight id="5008"> lhapdf=13008 </weight>
#<weight id="5009"> lhapdf=13009 </weight>
#<weight id="5010"> lhapdf=13010 </weight>
#<weight id="5011"> lhapdf=13011 </weight>
#<weight id="5012"> lhapdf=13012 </weight>
#<weight id="5013"> lhapdf=13013 </weight>
#<weight id="5014"> lhapdf=13014 </weight>
#<weight id="5015"> lhapdf=13015 </weight>
#<weight id="5016"> lhapdf=13016 </weight>
#<weight id="5017"> lhapdf=13017 </weight>
#<weight id="5018"> lhapdf=13018 </weight>
#<weight id="5019"> lhapdf=13019 </weight>
#<weight id="5020"> lhapdf=13020 </weight>
#<weight id="5021"> lhapdf=13021 </weight>
#<weight id="5022"> lhapdf=13022 </weight>
#<weight id="5023"> lhapdf=13023 </weight>
#<weight id="5024"> lhapdf=13024 </weight>
#<weight id="5025"> lhapdf=13025 </weight>
#<weight id="5026"> lhapdf=13026 </weight>
#<weight id="5027"> lhapdf=13027 </weight>
#<weight id="5028"> lhapdf=13028 </weight>
#<weight id="5029"> lhapdf=13029 </weight>
#<weight id="5030"> lhapdf=13030 </weight>
#<weight id="5031"> lhapdf=13031 </weight>
#<weight id="5032"> lhapdf=13032 </weight>
#<weight id="5033"> lhapdf=13033 </weight>
#<weight id="5034"> lhapdf=13034 </weight>
#<weight id="5035"> lhapdf=13035 </weight>
#<weight id="5036"> lhapdf=13036 </weight>
#<weight id="5037"> lhapdf=13037 </weight>
#<weight id="5038"> lhapdf=13038 </weight>
#<weight id="5039"> lhapdf=13039 </weight>
#<weight id="5040"> lhapdf=13040 </weight>
#<weight id="5041"> lhapdf=13041 </weight>
#<weight id="5042"> lhapdf=13042 </weight>
#<weight id="5043"> lhapdf=13043 </weight>
#<weight id="5044"> lhapdf=13044 </weight>
#<weight id="5045"> lhapdf=13045 </weight>
#<weight id="5046"> lhapdf=13046 </weight>
#<weight id="5047"> lhapdf=13047 </weight>
#<weight id="5048"> lhapdf=13048 </weight>
#<weight id="5049"> lhapdf=13049 </weight>
#<weight id="5050"> lhapdf=13050 </weight>
#<weight id="5051"> lhapdf=13051 </weight>
#<weight id="5052"> lhapdf=13052 </weight>
#<weight id="5053"> lhapdf=13053 </weight>
#<weight id="5054"> lhapdf=13054 </weight>
#<weight id="5055"> lhapdf=13055 </weight>
#<weight id="5056"> lhapdf=13056 </weight>
#<weight id="5060"> lhapdf=13065 </weight>
#<weight id="5070"> lhapdf=13069 </weight>
#<weight id="4000"> lhapdf=13100 </weight>
#<weight id="4001"> lhapdf=13101 </weight>
#<weight id="4002"> lhapdf=13102 </weight>
#<weight id="4003"> lhapdf=13103 </weight>
#<weight id="4004"> lhapdf=13104 </weight>
#<weight id="4005"> lhapdf=13105 </weight>
#<weight id="4006"> lhapdf=13106 </weight>
#<weight id="4007"> lhapdf=13107 </weight>
#<weight id="4008"> lhapdf=13108 </weight>
#<weight id="4009"> lhapdf=13109 </weight>
#<weight id="4010"> lhapdf=13110 </weight>
#<weight id="4011"> lhapdf=13111 </weight>
#<weight id="4012"> lhapdf=13112 </weight>
#<weight id="4013"> lhapdf=13113 </weight>
#<weight id="4014"> lhapdf=13114 </weight>
#<weight id="4015"> lhapdf=13115 </weight>
#<weight id="4016"> lhapdf=13116 </weight>
#<weight id="4017"> lhapdf=13117 </weight>
#<weight id="4018"> lhapdf=13118 </weight>
#<weight id="4019"> lhapdf=13119 </weight>
#<weight id="4020"> lhapdf=13120 </weight>
#<weight id="4021"> lhapdf=13121 </weight>
#<weight id="4022"> lhapdf=13122 </weight>
#<weight id="4023"> lhapdf=13123 </weight>
#<weight id="4024"> lhapdf=13124 </weight>
#<weight id="4025"> lhapdf=13125 </weight>
#<weight id="4026"> lhapdf=13126 </weight>
#<weight id="4027"> lhapdf=13127 </weight>
#<weight id="4028"> lhapdf=13128 </weight>
#<weight id="4029"> lhapdf=13129 </weight>
#<weight id="4030"> lhapdf=13130 </weight>
#<weight id="4031"> lhapdf=13131 </weight>
#<weight id="4032"> lhapdf=13132 </weight>
#<weight id="4033"> lhapdf=13133 </weight>
#<weight id="4034"> lhapdf=13134 </weight>
#<weight id="4035"> lhapdf=13135 </weight>
#<weight id="4036"> lhapdf=13136 </weight>
#<weight id="4037"> lhapdf=13137 </weight>
#<weight id="4038"> lhapdf=13138 </weight>
#<weight id="4039"> lhapdf=13139 </weight>
#<weight id="4040"> lhapdf=13140 </weight>
#<weight id="4041"> lhapdf=13141 </weight>
#<weight id="4042"> lhapdf=13142 </weight>
#<weight id="4043"> lhapdf=13143 </weight>
#<weight id="4044"> lhapdf=13144 </weight>
#<weight id="4045"> lhapdf=13145 </weight>
#<weight id="4046"> lhapdf=13146 </weight>
#<weight id="4047"> lhapdf=13147 </weight>
#<weight id="4048"> lhapdf=13148 </weight>
#<weight id="4049"> lhapdf=13149 </weight>
#<weight id="4050"> lhapdf=13150 </weight>
#<weight id="4051"> lhapdf=13151 </weight>
#<weight id="4052"> lhapdf=13152 </weight>
#<weight id="4053"> lhapdf=13153 </weight>
#<weight id="4054"> lhapdf=13154 </weight>
#<weight id="4055"> lhapdf=13155 </weight>
#<weight id="4056"> lhapdf=13156 </weight>
#<weight id="4060"> lhapdf=13163 </weight>
#<weight id="4070"> lhapdf=13167 </weight>
#<weight id="4080"> lhapdf=13200 </weight>
#<weight id="6000"> lhapdf=25200 </weight>
#<weight id="6001"> lhapdf=25201 </weight>
#<weight id="6002"> lhapdf=25202 </weight>
#<weight id="6003"> lhapdf=25203 </weight>
#<weight id="6004"> lhapdf=25204 </weight>
#<weight id="6005"> lhapdf=25205 </weight>
#<weight id="6006"> lhapdf=25206 </weight>
#<weight id="6007"> lhapdf=25207 </weight>
#<weight id="6008"> lhapdf=25208 </weight>
#<weight id="6009"> lhapdf=25209 </weight>
#<weight id="6010"> lhapdf=25210 </weight>
#<weight id="6011"> lhapdf=25211 </weight>
#<weight id="6012"> lhapdf=25212 </weight>
#<weight id="6013"> lhapdf=25213 </weight>
#<weight id="6014"> lhapdf=25214 </weight>
#<weight id="6015"> lhapdf=25215 </weight>
#<weight id="6016"> lhapdf=25216 </weight>
#<weight id="6017"> lhapdf=25217 </weight>
#<weight id="6018"> lhapdf=25218 </weight>
#<weight id="6019"> lhapdf=25219 </weight>
#<weight id="6020"> lhapdf=25220 </weight>
#<weight id="6021"> lhapdf=25221 </weight>
#<weight id="6022"> lhapdf=25222 </weight>
#<weight id="6023"> lhapdf=25223 </weight>
#<weight id="6024"> lhapdf=25224 </weight>
#<weight id="6025"> lhapdf=25225 </weight>
#<weight id="6026"> lhapdf=25226 </weight>
#<weight id="6027"> lhapdf=25227 </weight>
#<weight id="6028"> lhapdf=25228 </weight>
#<weight id="6029"> lhapdf=25229 </weight>
#<weight id="6030"> lhapdf=25230 </weight>
#<weight id="6031"> lhapdf=25231 </weight>
#<weight id="6032"> lhapdf=25232 </weight>
#<weight id="6033"> lhapdf=25233 </weight>
#<weight id="6034"> lhapdf=25234 </weight>
#<weight id="6035"> lhapdf=25235 </weight>
#<weight id="6036"> lhapdf=25236 </weight>
#<weight id="6037"> lhapdf=25237 </weight>
#<weight id="6038"> lhapdf=25238 </weight>
#<weight id="6039"> lhapdf=25239 </weight>
#<weight id="6040"> lhapdf=25240 </weight>
#<weight id="6041"> lhapdf=25241 </weight>
#<weight id="6042"> lhapdf=25242 </weight>
#<weight id="6043"> lhapdf=25243 </weight>
#<weight id="6044"> lhapdf=25244 </weight>
#<weight id="6045"> lhapdf=25245 </weight>
#<weight id="6046"> lhapdf=25246 </weight>
#<weight id="6047"> lhapdf=25247 </weight>
#<weight id="6048"> lhapdf=25248 </weight>
#<weight id="6049"> lhapdf=25249 </weight>
#<weight id="6050"> lhapdf=25250 </weight>
#<weight id="7000"> lhapdf=25300 </weight>
#<weight id="7001"> lhapdf=25301 </weight>
#<weight id="7002"> lhapdf=25302 </weight>
#<weight id="7003"> lhapdf=25303 </weight>
#<weight id="7004"> lhapdf=25304 </weight>
#<weight id="7005"> lhapdf=25305 </weight>
#<weight id="7006"> lhapdf=25306 </weight>
#<weight id="7007"> lhapdf=25307 </weight>
#<weight id="7008"> lhapdf=25308 </weight>
#<weight id="7009"> lhapdf=25309 </weight>
#<weight id="7010"> lhapdf=25310 </weight>
#<weight id="7011"> lhapdf=25311 </weight>
#<weight id="7012"> lhapdf=25312 </weight>
#<weight id="7013"> lhapdf=25313 </weight>
#<weight id="7014"> lhapdf=25314 </weight>
#<weight id="7015"> lhapdf=25315 </weight>
#<weight id="7016"> lhapdf=25316 </weight>
#<weight id="7017"> lhapdf=25317 </weight>
#<weight id="7018"> lhapdf=25318 </weight>
#<weight id="7019"> lhapdf=25319 </weight>
#<weight id="7020"> lhapdf=25320 </weight>
#<weight id="7021"> lhapdf=25321 </weight>
#<weight id="7022"> lhapdf=25322 </weight>
#<weight id="7023"> lhapdf=25323 </weight>
#<weight id="7024"> lhapdf=25324 </weight>
#<weight id="7025"> lhapdf=25325 </weight>
#<weight id="7026"> lhapdf=25326 </weight>
#<weight id="7027"> lhapdf=25327 </weight>
#<weight id="7028"> lhapdf=25328 </weight>
#<weight id="7029"> lhapdf=25329 </weight>
#<weight id="7030"> lhapdf=25330 </weight>
#<weight id="7031"> lhapdf=25331 </weight>
#<weight id="7032"> lhapdf=25332 </weight>
#<weight id="7033"> lhapdf=25333 </weight>
#<weight id="7034"> lhapdf=25334 </weight>
#<weight id="7035"> lhapdf=25335 </weight>
#<weight id="7036"> lhapdf=25336 </weight>
#<weight id="7037"> lhapdf=25337 </weight>
#<weight id="7038"> lhapdf=25338 </weight>
#<weight id="7039"> lhapdf=25339 </weight>
#<weight id="7040"> lhapdf=25340 </weight>
#<weight id="7041"> lhapdf=25341 </weight>
#<weight id="7042"> lhapdf=25342 </weight>
#<weight id="7043"> lhapdf=25343 </weight>
#<weight id="7044"> lhapdf=25344 </weight>
#<weight id="7045"> lhapdf=25345 </weight>
#<weight id="7046"> lhapdf=25346 </weight>
#<weight id="7047"> lhapdf=25347 </weight>
#<weight id="7048"> lhapdf=25348 </weight>
#<weight id="7049"> lhapdf=25349 </weight>
#<weight id="7050"> lhapdf=25350 </weight>
#<weight id="7060"> lhapdf=25000 </weight>
#<weight id="8000"> lhapdf=42780 </weight>
#<weight id="8001"> lhapdf=42781 </weight>
#<weight id="8002"> lhapdf=42782 </weight>
#<weight id="8003"> lhapdf=42783 </weight>
#<weight id="8004"> lhapdf=42784 </weight>
#<weight id="8005"> lhapdf=42785 </weight>
#<weight id="8006"> lhapdf=42786 </weight>
#<weight id="8007"> lhapdf=42787 </weight>
#<weight id="8008"> lhapdf=42788 </weight>
#<weight id="8009"> lhapdf=42789 </weight>
#<weight id="8010"> lhapdf=42790 </weight>
#<weight id="8011"> lhapdf=42791 </weight>
#<weight id="8012"> lhapdf=42792 </weight>
#<weight id="8013"> lhapdf=42793 </weight>
#<weight id="8014"> lhapdf=42794 </weight>
#<weight id="8015"> lhapdf=42795 </weight>
#<weight id="8016"> lhapdf=42796 </weight>
#<weight id="8017"> lhapdf=42797 </weight>
#<weight id="8018"> lhapdf=42798 </weight>
#<weight id="8019"> lhapdf=42799 </weight>
#<weight id="8020"> lhapdf=42800 </weight>
#<weight id="8021"> lhapdf=42801 </weight>
#<weight id="8022"> lhapdf=42802 </weight>
#<weight id="8023"> lhapdf=42803 </weight>
#<weight id="8024"> lhapdf=42804 </weight>
#<weight id="8025"> lhapdf=42805 </weight>
#<weight id="8026"> lhapdf=42806 </weight>
#<weight id="8027"> lhapdf=42807 </weight>
#<weight id="8028"> lhapdf=42808 </weight>
#<weight id="8029"> lhapdf=42809 </weight>
#<weight id="8500"> lhapdf=90200 </weight>
#<weight id="8501"> lhapdf=90201 </weight>
#<weight id="8502"> lhapdf=90202 </weight>
#<weight id="8503"> lhapdf=90203 </weight>
#<weight id="8504"> lhapdf=90204 </weight>
#<weight id="8505"> lhapdf=90205 </weight>
#<weight id="8506"> lhapdf=90206 </weight>
#<weight id="8507"> lhapdf=90207 </weight>
#<weight id="8508"> lhapdf=90208 </weight>
#<weight id="8509"> lhapdf=90209 </weight>
#<weight id="8510"> lhapdf=90210 </weight>
#<weight id="8511"> lhapdf=90211 </weight>
#<weight id="8512"> lhapdf=90212 </weight>
#<weight id="8513"> lhapdf=90213 </weight>
#<weight id="8514"> lhapdf=90214 </weight>
#<weight id="8515"> lhapdf=90215 </weight>
#<weight id="8516"> lhapdf=90216 </weight>
#<weight id="8517"> lhapdf=90217 </weight>
#<weight id="8518"> lhapdf=90218 </weight>
#<weight id="8519"> lhapdf=90219 </weight>
#<weight id="8520"> lhapdf=90220 </weight>
#<weight id="8521"> lhapdf=90221 </weight>
#<weight id="8522"> lhapdf=90222 </weight>
#<weight id="8523"> lhapdf=90223 </weight>
#<weight id="8524"> lhapdf=90224 </weight>
#<weight id="8525"> lhapdf=90225 </weight>
#<weight id="8526"> lhapdf=90226 </weight>
#<weight id="8527"> lhapdf=90227 </weight>
#<weight id="8528"> lhapdf=90228 </weight>
#<weight id="8529"> lhapdf=90229 </weight>
#<weight id="8530"> lhapdf=90230 </weight>
#<weight id="8531"> lhapdf=90231 </weight>
#<weight id="8532"> lhapdf=90232 </weight>
#<weight id="8533"> lhapdf=90233 </weight>
#<weight id="8534"> lhapdf=90234 </weight>
#<weight id="8535"> lhapdf=90235 </weight>
#<weight id="8536"> lhapdf=90236 </weight>
#<weight id="8537"> lhapdf=90237 </weight>
#<weight id="8538"> lhapdf=90238 </weight>
#<weight id="8539"> lhapdf=90239 </weight>
#<weight id="8540"> lhapdf=90240 </weight>
#<weight id="8541"> lhapdf=90241 </weight>
#<weight id="8542"> lhapdf=90242 </weight>
#<weight id="8543"> lhapdf=90243 </weight>
#<weight id="8544"> lhapdf=90244 </weight>
#<weight id="8545"> lhapdf=90245 </weight>
#<weight id="8546"> lhapdf=90246 </weight>
#<weight id="8547"> lhapdf=90247 </weight>
#<weight id="8548"> lhapdf=90248 </weight>
#<weight id="8549"> lhapdf=90249 </weight>
#<weight id="8550"> lhapdf=90250 </weight>
#<weight id="8551"> lhapdf=90251 </weight>
#<weight id="8552"> lhapdf=90252 </weight>
#<weight id="8553"> lhapdf=90253 </weight>
#<weight id="8554"> lhapdf=90254 </weight>
#<weight id="8555"> lhapdf=90255 </weight>
#<weight id="8556"> lhapdf=90256 </weight>
#<weight id="8557"> lhapdf=90257 </weight>
#<weight id="8558"> lhapdf=90258 </weight>
#<weight id="8559"> lhapdf=90259 </weight>
#<weight id="8560"> lhapdf=90260 </weight>
#<weight id="8561"> lhapdf=90261 </weight>
#<weight id="8562"> lhapdf=90262 </weight>
#<weight id="8563"> lhapdf=90263 </weight>
#<weight id="8564"> lhapdf=90264 </weight>
#<weight id="8565"> lhapdf=90265 </weight>
#<weight id="8566"> lhapdf=90266 </weight>
#<weight id="8567"> lhapdf=90267 </weight>
#<weight id="8568"> lhapdf=90268 </weight>
#<weight id="8569"> lhapdf=90269 </weight>
#<weight id="8570"> lhapdf=90270 </weight>
#<weight id="8571"> lhapdf=90271 </weight>
#<weight id="8572"> lhapdf=90272 </weight>
#<weight id="8573"> lhapdf=90273 </weight>
#<weight id="8574"> lhapdf=90274 </weight>
#<weight id="8575"> lhapdf=90275 </weight>
#<weight id="8576"> lhapdf=90276 </weight>
#<weight id="8577"> lhapdf=90277 </weight>
#<weight id="8578"> lhapdf=90278 </weight>
#<weight id="8579"> lhapdf=90279 </weight>
#<weight id="8580"> lhapdf=90280 </weight>
#<weight id="8581"> lhapdf=90281 </weight>
#<weight id="8582"> lhapdf=90282 </weight>
#<weight id="8583"> lhapdf=90283 </weight>
#<weight id="8584"> lhapdf=90284 </weight>
#<weight id="8585"> lhapdf=90285 </weight>
#<weight id="8586"> lhapdf=90286 </weight>
#<weight id="8587"> lhapdf=90287 </weight>
#<weight id="8588"> lhapdf=90288 </weight>
#<weight id="8589"> lhapdf=90289 </weight>
#<weight id="8590"> lhapdf=90290 </weight>
#<weight id="8591"> lhapdf=90291 </weight>
#<weight id="8592"> lhapdf=90292 </weight>
#<weight id="8593"> lhapdf=90293 </weight>
#<weight id="8594"> lhapdf=90294 </weight>
#<weight id="8595"> lhapdf=90295 </weight>
#<weight id="8596"> lhapdf=90296 </weight>
#<weight id="8597"> lhapdf=90297 </weight>
#<weight id="8598"> lhapdf=90298 </weight>
#<weight id="8599"> lhapdf=90299 </weight>
#<weight id="8600"> lhapdf=90300 </weight>
#<weight id="8601"> lhapdf=90301 </weight>
#<weight id="8602"> lhapdf=90302 </weight>
#<weight id="9000"> lhapdf=91200 </weight>
#<weight id="9001"> lhapdf=91201 </weight>
#<weight id="9002"> lhapdf=91202 </weight>
#<weight id="9003"> lhapdf=91203 </weight>
#<weight id="9004"> lhapdf=91204 </weight>
#<weight id="9005"> lhapdf=91205 </weight>
#<weight id="9006"> lhapdf=91206 </weight>
#<weight id="9007"> lhapdf=91207 </weight>
#<weight id="9008"> lhapdf=91208 </weight>
#<weight id="9009"> lhapdf=91209 </weight>
#<weight id="9010"> lhapdf=91210 </weight>
#<weight id="9011"> lhapdf=91211 </weight>
#<weight id="9012"> lhapdf=91212 </weight>
#<weight id="9013"> lhapdf=91213 </weight>
#<weight id="9014"> lhapdf=91214 </weight>
#<weight id="9015"> lhapdf=91215 </weight>
#<weight id="9016"> lhapdf=91216 </weight>
#<weight id="9017"> lhapdf=91217 </weight>
#<weight id="9018"> lhapdf=91218 </weight>
#<weight id="9019"> lhapdf=91219 </weight>
#<weight id="9020"> lhapdf=91220 </weight>
#<weight id="9021"> lhapdf=91221 </weight>
#<weight id="9022"> lhapdf=91222 </weight>
#<weight id="9023"> lhapdf=91223 </weight>
#<weight id="9024"> lhapdf=91224 </weight>
#<weight id="9025"> lhapdf=91225 </weight>
#<weight id="9026"> lhapdf=91226 </weight>
#<weight id="9027"> lhapdf=91227 </weight>
#<weight id="9028"> lhapdf=91228 </weight>
#<weight id="9029"> lhapdf=91229 </weight>
#<weight id="9030"> lhapdf=91230 </weight>
#<weight id="9031"> lhapdf=91231 </weight>
#<weight id="9032"> lhapdf=91232 </weight>
#<weight id="9033"> lhapdf=91233 </weight>
#<weight id="9034"> lhapdf=91234 </weight>
#<weight id="9035"> lhapdf=91235 </weight>
#<weight id="9036"> lhapdf=91236 </weight>
#<weight id="9037"> lhapdf=91237 </weight>
#<weight id="9038"> lhapdf=91238 </weight>
#<weight id="9039"> lhapdf=91239 </weight>
#<weight id="9040"> lhapdf=91240 </weight>
#<weight id="9041"> lhapdf=91241 </weight>
#<weight id="9042"> lhapdf=91242 </weight>
#<weight id="9043"> lhapdf=91243 </weight>
#<weight id="9044"> lhapdf=91244 </weight>
#<weight id="9045"> lhapdf=91245 </weight>
#<weight id="9046"> lhapdf=91246 </weight>
#<weight id="9047"> lhapdf=91247 </weight>
#<weight id="9048"> lhapdf=91248 </weight>
#<weight id="9049"> lhapdf=91249 </weight>
#<weight id="9050"> lhapdf=91250 </weight>
#<weight id="9051"> lhapdf=91251 </weight>
#<weight id="9052"> lhapdf=91252 </weight>
#<weight id="9053"> lhapdf=91253 </weight>
#<weight id="9054"> lhapdf=91254 </weight>
#<weight id="9055"> lhapdf=91255 </weight>
#<weight id="9056"> lhapdf=91256 </weight>
#<weight id="9057"> lhapdf=91257 </weight>
#<weight id="9058"> lhapdf=91258 </weight>
#<weight id="9059"> lhapdf=91259 </weight>
#<weight id="9060"> lhapdf=91260 </weight>
#<weight id="9061"> lhapdf=91261 </weight>
#<weight id="9062"> lhapdf=91262 </weight>
#<weight id="9063"> lhapdf=91263 </weight>
#<weight id="9064"> lhapdf=91264 </weight>
#<weight id="9065"> lhapdf=91265 </weight>
#<weight id="9066"> lhapdf=91266 </weight>
#<weight id="9067"> lhapdf=91267 </weight>
#<weight id="9068"> lhapdf=91268 </weight>
#<weight id="9069"> lhapdf=91269 </weight>
#<weight id="9070"> lhapdf=91270 </weight>
#<weight id="9071"> lhapdf=91271 </weight>
#<weight id="9072"> lhapdf=91272 </weight>
#<weight id="9073"> lhapdf=91273 </weight>
#<weight id="9074"> lhapdf=91274 </weight>
#<weight id="9075"> lhapdf=91275 </weight>
#<weight id="9076"> lhapdf=91276 </weight>
#<weight id="9077"> lhapdf=91277 </weight>
#<weight id="9078"> lhapdf=91278 </weight>
#<weight id="9079"> lhapdf=91279 </weight>
#<weight id="9080"> lhapdf=91280 </weight>
#<weight id="9081"> lhapdf=91281 </weight>
#<weight id="9082"> lhapdf=91282 </weight>
#<weight id="9083"> lhapdf=91283 </weight>
#<weight id="9084"> lhapdf=91284 </weight>
#<weight id="9085"> lhapdf=91285 </weight>
#<weight id="9086"> lhapdf=91286 </weight>
#<weight id="9087"> lhapdf=91287 </weight>
#<weight id="9088"> lhapdf=91288 </weight>
#<weight id="9089"> lhapdf=91289 </weight>
#<weight id="9090"> lhapdf=91290 </weight>
#<weight id="9091"> lhapdf=91291 </weight>
#<weight id="9092"> lhapdf=91292 </weight>
#<weight id="9093"> lhapdf=91293 </weight>
#<weight id="9094"> lhapdf=91294 </weight>
#<weight id="9095"> lhapdf=91295 </weight>
#<weight id="9096"> lhapdf=91296 </weight>
#<weight id="9097"> lhapdf=91297 </weight>
#<weight id="9098"> lhapdf=91298 </weight>
#<weight id="9099"> lhapdf=91299 </weight>
#<weight id="9100"> lhapdf=91300 </weight>
#<weight id="9101"> lhapdf=91301 </weight>
#<weight id="9102"> lhapdf=91302 </weight>
#<weight id="10000"> lhapdf=90400 </weight>
#<weight id="10001"> lhapdf=90401 </weight>
#<weight id="10002"> lhapdf=90402 </weight>
#<weight id="10003"> lhapdf=90403 </weight>
#<weight id="10004"> lhapdf=90404 </weight>
#<weight id="10005"> lhapdf=90405 </weight>
#<weight id="10006"> lhapdf=90406 </weight>
#<weight id="10007"> lhapdf=90407 </weight>
#<weight id="10008"> lhapdf=90408 </weight>
#<weight id="10009"> lhapdf=90409 </weight>
#<weight id="10010"> lhapdf=90410 </weight>
#<weight id="10011"> lhapdf=90411 </weight>
#<weight id="10012"> lhapdf=90412 </weight>
#<weight id="10013"> lhapdf=90413 </weight>
#<weight id="10014"> lhapdf=90414 </weight>
#<weight id="10015"> lhapdf=90415 </weight>
#<weight id="10016"> lhapdf=90416 </weight>
#<weight id="10017"> lhapdf=90417 </weight>
#<weight id="10018"> lhapdf=90418 </weight>
#<weight id="10019"> lhapdf=90419 </weight>
#<weight id="10020"> lhapdf=90420 </weight>
#<weight id="10021"> lhapdf=90421 </weight>
#<weight id="10022"> lhapdf=90422 </weight>
#<weight id="10023"> lhapdf=90423 </weight>
#<weight id="10024"> lhapdf=90424 </weight>
#<weight id="10025"> lhapdf=90425 </weight>
#<weight id="10026"> lhapdf=90426 </weight>
#<weight id="10027"> lhapdf=90427 </weight>
#<weight id="10028"> lhapdf=90428 </weight>
#<weight id="10029"> lhapdf=90429 </weight>
#<weight id="10030"> lhapdf=90430 </weight>
#<weight id="10031"> lhapdf=90431 </weight>
#<weight id="10032"> lhapdf=90432 </weight>
#<weight id="11000"> lhapdf=91400 </weight>
#<weight id="11001"> lhapdf=91401 </weight>
#<weight id="11002"> lhapdf=91402 </weight>
#<weight id="11003"> lhapdf=91403 </weight>
#<weight id="11004"> lhapdf=91404 </weight>
#<weight id="11005"> lhapdf=91405 </weight>
#<weight id="11006"> lhapdf=91406 </weight>
#<weight id="11007"> lhapdf=91407 </weight>
#<weight id="11008"> lhapdf=91408 </weight>
#<weight id="11009"> lhapdf=91409 </weight>
#<weight id="11010"> lhapdf=91410 </weight>
#<weight id="11011"> lhapdf=91411 </weight>
#<weight id="11012"> lhapdf=91412 </weight>
#<weight id="11013"> lhapdf=91413 </weight>
#<weight id="11014"> lhapdf=91414 </weight>
#<weight id="11015"> lhapdf=91415 </weight>
#<weight id="11016"> lhapdf=91416 </weight>
#<weight id="11017"> lhapdf=91417 </weight>
#<weight id="11018"> lhapdf=91418 </weight>
#<weight id="11019"> lhapdf=91419 </weight>
#<weight id="11020"> lhapdf=91420 </weight>
#<weight id="11021"> lhapdf=91421 </weight>
#<weight id="11022"> lhapdf=91422 </weight>
#<weight id="11023"> lhapdf=91423 </weight>
#<weight id="11024"> lhapdf=91424 </weight>
#<weight id="11025"> lhapdf=91425 </weight>
#<weight id="11026"> lhapdf=91426 </weight>
#<weight id="11027"> lhapdf=91427 </weight>
#<weight id="11028"> lhapdf=91428 </weight>
#<weight id="11029"> lhapdf=91429 </weight>
#<weight id="11030"> lhapdf=91430 </weight>
#<weight id="11031"> lhapdf=91431 </weight>
#<weight id="11032"> lhapdf=91432 </weight>
#<weight id="12000"> lhapdf=61100 </weight>
#<weight id="12001"> lhapdf=61101 </weight>
#<weight id="12002"> lhapdf=61102 </weight>
#<weight id="12003"> lhapdf=61103 </weight>
#<weight id="12004"> lhapdf=61104 </weight>
#<weight id="12005"> lhapdf=61105 </weight>
#<weight id="12006"> lhapdf=61106 </weight>
#<weight id="12007"> lhapdf=61107 </weight>
#<weight id="12008"> lhapdf=61108 </weight>
#<weight id="12009"> lhapdf=61109 </weight>
#<weight id="12010"> lhapdf=61110 </weight>
#<weight id="12011"> lhapdf=61111 </weight>
#<weight id="12012"> lhapdf=61112 </weight>
#<weight id="12013"> lhapdf=61113 </weight>
#<weight id="12014"> lhapdf=61114 </weight>
#<weight id="12015"> lhapdf=61115 </weight>
#<weight id="12016"> lhapdf=61116 </weight>
#<weight id="12017"> lhapdf=61117 </weight>
#<weight id="12018"> lhapdf=61118 </weight>
#<weight id="12019"> lhapdf=61119 </weight>
#<weight id="12020"> lhapdf=61120 </weight>
#<weight id="12021"> lhapdf=61121 </weight>
#<weight id="12022"> lhapdf=61122 </weight>
#<weight id="12023"> lhapdf=61123 </weight>
#<weight id="12024"> lhapdf=61124 </weight>
#<weight id="12025"> lhapdf=61125 </weight>
#<weight id="12026"> lhapdf=61126 </weight>
#<weight id="12027"> lhapdf=61127 </weight>
#<weight id="12028"> lhapdf=61128 </weight>
#<weight id="12050"> lhapdf=61130 </weight>
#<weight id="12051"> lhapdf=61131 </weight>
#<weight id="12052"> lhapdf=61132 </weight>
#<weight id="12053"> lhapdf=61133 </weight>
#<weight id="12054"> lhapdf=61134 </weight>
#<weight id="12055"> lhapdf=61135 </weight>
#<weight id="12056"> lhapdf=61136 </weight>
#<weight id="12057"> lhapdf=61137 </weight>
#<weight id="12058"> lhapdf=61138 </weight>
#<weight id="12059"> lhapdf=61139 </weight>
#<weight id="12060"> lhapdf=61140 </weight>
#<weight id="12061"> lhapdf=61141 </weight>
#<weight id="12062"> lhapdf=61142 </weight>
#<weight id="12063"> lhapdf=61143 </weight>
#<weight id="13000"> lhapdf=61200 </weight>
#<weight id="13001"> lhapdf=61201 </weight>
#<weight id="13002"> lhapdf=61202 </weight>
#<weight id="13003"> lhapdf=61203 </weight>
#<weight id="13004"> lhapdf=61204 </weight>
#<weight id="13005"> lhapdf=61205 </weight>
#<weight id="13006"> lhapdf=61206 </weight>
#<weight id="13007"> lhapdf=61207 </weight>
#<weight id="13008"> lhapdf=61208 </weight>
#<weight id="13009"> lhapdf=61209 </weight>
#<weight id="13010"> lhapdf=61210 </weight>
#<weight id="13011"> lhapdf=61211 </weight>
#<weight id="13012"> lhapdf=61212 </weight>
#<weight id="13013"> lhapdf=61213 </weight>
#<weight id="13014"> lhapdf=61214 </weight>
#<weight id="13015"> lhapdf=61215 </weight>
#<weight id="13016"> lhapdf=61216 </weight>
#<weight id="13017"> lhapdf=61217 </weight>
#<weight id="13018"> lhapdf=61218 </weight>
#<weight id="13019"> lhapdf=61219 </weight>
#<weight id="13020"> lhapdf=61220 </weight>
#<weight id="13021"> lhapdf=61221 </weight>
#<weight id="13022"> lhapdf=61222 </weight>
#<weight id="13023"> lhapdf=61223 </weight>
#<weight id="13024"> lhapdf=61224 </weight>
#<weight id="13025"> lhapdf=61225 </weight>
#<weight id="13026"> lhapdf=61226 </weight>
#<weight id="13027"> lhapdf=61227 </weight>
#<weight id="13028"> lhapdf=61228 </weight>
#<weight id="13050"> lhapdf=61230 </weight>
#<weight id="13051"> lhapdf=61231 </weight>
#<weight id="13052"> lhapdf=61232 </weight>
#<weight id="13053"> lhapdf=61233 </weight>
#<weight id="13054"> lhapdf=61234 </weight>
#<weight id="13055"> lhapdf=61235 </weight>
#<weight id="13056"> lhapdf=61236 </weight>
#<weight id="13057"> lhapdf=61237 </weight>
#<weight id="13058"> lhapdf=61238 </weight>
#<weight id="13059"> lhapdf=61239 </weight>
#<weight id="13060"> lhapdf=61240 </weight>
#<weight id="13061"> lhapdf=61241 </weight>
#<weight id="13062"> lhapdf=61242 </weight>
#<weight id="13063"> lhapdf=61243 </weight>
#<weight id="14000"> lhapdf=13400 </weight>
#<weight id="14001"> lhapdf=13401 </weight>
#<weight id="14002"> lhapdf=13402 </weight>
#<weight id="14003"> lhapdf=13403 </weight>
#<weight id="14004"> lhapdf=13404 </weight>
#<weight id="14005"> lhapdf=13405 </weight>
#<weight id="14006"> lhapdf=13406 </weight>
#<weight id="14007"> lhapdf=13407 </weight>
#<weight id="14008"> lhapdf=13408 </weight>
#<weight id="14009"> lhapdf=13409 </weight>
#<weight id="14010"> lhapdf=13410 </weight>
#<weight id="14011"> lhapdf=13411 </weight>
#<weight id="14012"> lhapdf=13412 </weight>
#<weight id="14013"> lhapdf=13413 </weight>
#<weight id="14014"> lhapdf=13414 </weight>
#<weight id="14015"> lhapdf=13415 </weight>
#<weight id="14016"> lhapdf=13416 </weight>
#<weight id="14017"> lhapdf=13417 </weight>
#<weight id="14018"> lhapdf=13418 </weight>
#<weight id="14019"> lhapdf=13419 </weight>
#<weight id="14020"> lhapdf=13420 </weight>
#<weight id="14021"> lhapdf=13421 </weight>
#<weight id="14022"> lhapdf=13422 </weight>
#<weight id="14023"> lhapdf=13423 </weight>
#<weight id="14024"> lhapdf=13424 </weight>
#<weight id="14025"> lhapdf=13425 </weight>
#<weight id="14026"> lhapdf=13426 </weight>
#<weight id="14027"> lhapdf=13427 </weight>
#<weight id="14028"> lhapdf=13428 </weight>
#<weight id="14029"> lhapdf=13429 </weight>
#<weight id="14030"> lhapdf=13430 </weight>
#<weight id="15000"> lhapdf=82200 </weight>
#<weight id="15001"> lhapdf=82201 </weight>
#<weight id="15002"> lhapdf=82202 </weight>
#<weight id="15003"> lhapdf=82203 </weight>
#<weight id="15004"> lhapdf=82204 </weight>
#<weight id="15005"> lhapdf=82205 </weight>
#<weight id="15006"> lhapdf=82206 </weight>
#<weight id="15007"> lhapdf=82207 </weight>
#<weight id="15008"> lhapdf=82208 </weight>
#<weight id="15009"> lhapdf=82209 </weight>
#<weight id="15010"> lhapdf=82210 </weight>
#<weight id="15011"> lhapdf=82211 </weight>
#<weight id="15012"> lhapdf=82212 </weight>
#<weight id="15013"> lhapdf=82213 </weight>
#<weight id="15014"> lhapdf=82214 </weight>
#<weight id="15015"> lhapdf=82215 </weight>
#<weight id="15016"> lhapdf=82216 </weight>
#<weight id="15017"> lhapdf=82217 </weight>
#<weight id="15018"> lhapdf=82218 </weight>
#<weight id="15019"> lhapdf=82219 </weight>
#<weight id="15020"> lhapdf=82220 </weight>
#<weight id="15021"> lhapdf=82221 </weight>
#<weight id="15022"> lhapdf=82222 </weight>
#<weight id="15023"> lhapdf=82223 </weight>
#<weight id="15024"> lhapdf=82224 </weight>
#<weight id="15025"> lhapdf=82225 </weight>
#<weight id="15026"> lhapdf=82226 </weight>
#<weight id="15027"> lhapdf=82227 </weight>
#<weight id="15028"> lhapdf=82228 </weight>
#<weight id="15029"> lhapdf=82229 </weight>
#<weight id="15030"> lhapdf=82230 </weight>
#<weight id="15031"> lhapdf=82231 </weight>
#<weight id="15032"> lhapdf=82232 </weight>
#<weight id="15033"> lhapdf=82233 </weight>
#<weight id="15034"> lhapdf=82234 </weight>
#<weight id="15035"> lhapdf=82235 </weight>
#<weight id="15036"> lhapdf=82236 </weight>
#<weight id="15037"> lhapdf=82237 </weight>
#<weight id="15038"> lhapdf=82238 </weight>
#<weight id="15039"> lhapdf=82239 </weight>
#<weight id="15040"> lhapdf=82240 </weight>
#<weight id="15041"> lhapdf=82241 </weight>
#<weight id="15042"> lhapdf=82242 </weight>
#<weight id="15043"> lhapdf=82243 </weight>
#<weight id="15044"> lhapdf=82244 </weight>
#<weight id="15045"> lhapdf=82245 </weight>
#<weight id="15046"> lhapdf=82246 </weight>
#<weight id="15047"> lhapdf=82247 </weight>
#<weight id="15048"> lhapdf=82248 </weight>
#<weight id="15049"> lhapdf=82249 </weight>
#<weight id="15050"> lhapdf=82250 </weight>
#<weight id="15051"> lhapdf=82251 </weight>
#<weight id="15052"> lhapdf=82252 </weight>
#<weight id="15053"> lhapdf=82253 </weight>
#<weight id="15054"> lhapdf=82254 </weight>
#<weight id="15055"> lhapdf=82255 </weight>
#<weight id="15056"> lhapdf=82256 </weight>
#<weight id="15057"> lhapdf=82257 </weight>
#<weight id="15058"> lhapdf=82258 </weight>
#<weight id="15059"> lhapdf=82259 </weight>
#<weight id="15060"> lhapdf=82260 </weight>
#<weight id="15061"> lhapdf=82261 </weight>
#<weight id="15062"> lhapdf=82262 </weight>
#<weight id="15063"> lhapdf=82263 </weight>
#<weight id="15064"> lhapdf=82264 </weight>
#<weight id="15065"> lhapdf=82265 </weight>
#<weight id="15066"> lhapdf=82266 </weight>
#<weight id="15067"> lhapdf=82267 </weight>
#<weight id="15068"> lhapdf=82268 </weight>
#<weight id="15069"> lhapdf=82269 </weight>
#<weight id="15070"> lhapdf=82270 </weight>
#<weight id="15071"> lhapdf=82271 </weight>
#<weight id="15072"> lhapdf=82272 </weight>
#<weight id="15073"> lhapdf=82273 </weight>
#<weight id="15074"> lhapdf=82274 </weight>
#<weight id="15075"> lhapdf=82275 </weight>
#<weight id="15076"> lhapdf=82276 </weight>
#<weight id="15077"> lhapdf=82277 </weight>
#<weight id="15078"> lhapdf=82278 </weight>
#<weight id="15079"> lhapdf=82279 </weight>
#<weight id="15080"> lhapdf=82280 </weight>
#<weight id="15081"> lhapdf=82281 </weight>
#<weight id="15082"> lhapdf=82282 </weight>
#<weight id="15083"> lhapdf=82283 </weight>
#<weight id="15084"> lhapdf=82284 </weight>
#<weight id="15085"> lhapdf=82285 </weight>
#<weight id="15086"> lhapdf=82286 </weight>
#<weight id="15087"> lhapdf=82287 </weight>
#<weight id="15088"> lhapdf=82288 </weight>
#<weight id="15089"> lhapdf=82289 </weight>
#<weight id="15090"> lhapdf=82290 </weight>
#<weight id="15091"> lhapdf=82291 </weight>
#<weight id="15092"> lhapdf=82292 </weight>
#<weight id="15093"> lhapdf=82293 </weight>
#<weight id="15094"> lhapdf=82294 </weight>
#<weight id="15095"> lhapdf=82295 </weight>
#<weight id="15096"> lhapdf=82296 </weight>
#<weight id="15097"> lhapdf=82297 </weight>
#<weight id="15098"> lhapdf=82298 </weight>
#<weight id="15099"> lhapdf=82299 </weight>
#<weight id="15100"> lhapdf=82300 </weight>
#<weight id="15101"> lhapdf=82301 </weight>
#<weight id="15102"> lhapdf=82302 </weight>
#<weight id="15103"> lhapdf=82303 </weight>
#<weight id="15104"> lhapdf=82304 </weight>
#<weight id="15105"> lhapdf=82305 </weight>
#<weight id="15106"> lhapdf=82306 </weight>
#<weight id="15107"> lhapdf=82307 </weight>
