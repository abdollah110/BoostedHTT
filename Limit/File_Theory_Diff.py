# Here we run on already skimmed samples and make the histograms

import ROOT
from ROOT import *
import glob

outFile=TFile('differential_theory_3.root','RECREATE')
tDirectory_hpt_powheg= outFile.mkdir('hpt_powheg')
tDirectory_hpt_nnlops= outFile.mkdir('hpt_nnlops')
tDirectory_jpt_powheg= outFile.mkdir('jpt_powheg')
tDirectory_jpt_nnlops= outFile.mkdir('jpt_nnlops')


uncertainties=[
 'Nominal',
 'THU_ggH_Mu',
 'THU_ggH_Res',
 'THU_ggH_Mig01',
 'THU_ggH_Mig12',
 'THU_ggH_VBF2j',
 'THU_ggH_VBF3j',
 'THU_ggH_PT60',
 'THU_ggH_PT120',
 'THU_ggH_qmtop',
 'scale'
 ]
 


DirectoryName='AllHiggs_v3_sys/'
allfile=glob.glob(DirectoryName+'/*htt125.root')
for f in allfile:
    file=TFile(f,'open')
    print file.GetName()
    for unc in uncertainties:
    
        hist=file.Get('HiggsPt'+'_'+unc.replace('scale','THU_ggH_Mu'))
        print hist.Integral()
        tDirectory_hpt_powheg.cd()
        tDirectory_hpt_powheg.WriteObject(hist,(f.replace(DirectoryName,'').replace('.root','')+'_'+unc).replace('_Nominal',''))
        
        hist=file.Get('HiggsPt_nnlops'+'_'+unc.replace('scale','THU_ggH_Mu'))
        print hist.Integral()
        tDirectory_hpt_nnlops.cd()
        tDirectory_hpt_nnlops.WriteObject(hist,(f.replace(DirectoryName,'').replace('.root','')+'_'+unc).replace('_Nominal',''))
        
        
        hist=file.Get('JetPt'+'_'+unc.replace('scale','THU_ggH_Mu'))
        print hist.Integral()
        tDirectory_jpt_powheg.cd()
        tDirectory_jpt_powheg.WriteObject(hist,(f.replace(DirectoryName,'').replace('.root','')+'_'+unc).replace('_Nominal',''))
        
        hist=file.Get('JetPt_nnlops'+'_'+unc.replace('scale','THU_ggH_Mu'))
        print hist.Integral()
        tDirectory_jpt_nnlops.cd()
        tDirectory_jpt_nnlops.WriteObject(hist,(f.replace(DirectoryName,'').replace('.root','')+'_'+unc).replace('_Nominal',''))
        
        
#        tDirectory.WriteObject(hist,f.replace('AllHiggs/','').replace('.root','')+'_'+unc)
#
#
#        for unc in uncertainties:
#            tDirectory.WriteObject(hist,f.replace('AllHiggs/','').replace('.root','')+'_'+unc)
#            tDirectory_nnlops.WriteObject(hist,f.replace('AllHiggs/','').replace('.root','')+'_'+unc)
    
outFile.Close()
