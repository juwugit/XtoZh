import os
from  ROOT import *
print "working"
def MakeCountingDataCard(status, inputdatacard):
    datacardname = 'Datacard_counting_%s.txt' %(status)
    os.system('rm -rf  '+datacardname)
    
 
    readfilename='Shape1d_0819.root' 
    file = TFile(readfilename,"READ") 
    

    #print type(histYield)
    DATAstr='data_obs' 
    SIGstr='signal' 
    DYstr='background_DY' 
    TTstr='background_TT' 
    ZZstr='background_ZZ'
    WZstr='background_WZ'  
    histYieldDATA = gROOT.FindObject(DATAstr)
    histYieldSIG = gROOT.FindObject(SIGstr)
    histYieldDY = gROOT.FindObject(DYstr)
    histYieldTT = gROOT.FindObject(TTstr)
    histYieldZZ = gROOT.FindObject(ZZstr)
    histYieldWZ = gROOT.FindObject(WZstr)
    histYieldWW = gROOT.FindObject(WWstr)
    datacard = open(datacardname,"a")
    for line in open(inputdatacard):

 

       #line = line.replace("ROOTFILENAME",str(status+'_'+etaregion+'_'+isolation+'_'+eveto+'.root'))

        line = line.replace("BK_DY",str(DYstr))
        line = line.replace("BK_TT",str(TTstr))
        line = line.replace("BK_ZZ",str(ZZstr))
        line = line.replace("INPUTHIST",str(readfilename))
        line = line.replace("NUMBEROBS",str(histYieldDATA.Integral()))
        line = line.replace("SIGRATE",str(histYieldSIG.Integral()))
        line = line.replace("DYRATE",str(histYieldDY.Integral()))
        line = line.replace("TTRATE",str(histYieldTT.Integral()))
        line = line.replace("ZZRATE",str(histYieldZZ.Integral()))
        line = line.replace("WZRATE",str(histYieldWZ.Integral()))
        line = line.replace("WWRATE",str(histYieldWW.Integral()))
        datacard.write(line)
    datacard.close()
    return 0.0


def MakeShape1dDataCard(status, inputdatacard):
    datacardname = 'Datacard_1dshape_%s.txt' %(status)
    os.system('rm -rf  '+datacardname)
    
 
    readfilename='Shape1d_0819.root' 
    file = TFile(readfilename,"READ") 
    

    #print type(histYield)
    DATAstr='data_obs' 
    SIGstr='signal' 
    DYstr='background_DY' 
    TTstr='background_TT' 
    ZZstr='background_ZZ' 
    WZstr='background_WZ'
    WWstr='background_WW'
    histYieldDATA = gROOT.FindObject(DATAstr)
    histYieldSIG = gROOT.FindObject(SIGstr)
    histYieldDY = gROOT.FindObject(DYstr)
    histYieldTT = gROOT.FindObject(TTstr)
    histYieldZZ = gROOT.FindObject(ZZstr)
    histYieldWZ = gROOT.FindObject(WZstr)
    histYieldWW = gROOT.FindObject(WWstr)
    datacard = open(datacardname,"a")
    for line in open(inputdatacard):

 

       #line = line.replace("ROOTFILENAME",str(status+'_'+etaregion+'_'+isolation+'_'+eveto+'.root'))

        line = line.replace("BK_DY",str(DYstr))
        line = line.replace("BK_TT",str(TTstr))
        line = line.replace("BK_ZZ",str(ZZstr))
        line = line.replace("INPUTHIST",str(readfilename))
        line = line.replace("NUMBEROBS",str(histYieldDATA.Integral()))
        line = line.replace("SIGRATE",str(histYieldSIG.Integral()))
        line = line.replace("DYRATE",str(histYieldDY.Integral()))
        line = line.replace("TTRATE",str(histYieldTT.Integral()))
        line = line.replace("ZZRATE",str(histYieldZZ.Integral()))       
        line = line.replace("WZRATE",str(histYieldWZ.Integral()))     
        line = line.replace("WWRATE",str(histYieldWW.Integral()))     
        datacard.write(line)
    datacard.close()
    return 0.0



def MakeDataCard(status, ibin, inputdatacard):
    datacardname = 'Datacard_%s_%d.txt' %(status,ibin)
    os.system('rm -rf  '+datacardname)
    
    
   
    readfilename='output_0819_%d.root' %ibin 
    file = TFile(readfilename,"READ") 
    

    #print type(histYield)
    DATAstr='data_obs' 
    SIGstr='signal_%d' %ibin
    DYstr='background_DY_%d' %ibin
    TTstr='background_TT_%d' %ibin
    ZZstr='background_ZZ_%d' %ibin
    WZstr='background_WZ_%d' %ibin
    WWstr='background_WW_%d' %ibin
    histYieldDATA = gROOT.FindObject(DATAstr)
    histYieldSIG = gROOT.FindObject(SIGstr)
    histYieldDY = gROOT.FindObject(DYstr)
    histYieldTT = gROOT.FindObject(TTstr)
    histYieldZZ = gROOT.FindObject(ZZstr)
    histYieldWZ = gROOT.FindObject(WZstr) 
    histYieldWW = gROOT.FindObject(WWstr) 
   
    datacard = open(datacardname,"a")
    for line in open(inputdatacard):

 

       #line = line.replace("ROOTFILENAME",str(status+'_'+etaregion+'_'+isolation+'_'+eveto+'.root'))

        line = line.replace("BK_DY",str(DYstr))
        line = line.replace("BK_TT",str(TTstr))
        line = line.replace("BK_ZZ",str(ZZstr))
        line = line.replace("BK_WZ",str(WZstr))
        line = line.replace("INPUTHIST",str(readfilename))
        line = line.replace("NUMBEROBS",str(histYieldDATA.Integral()))
        line = line.replace("SIGRATE",str(histYieldSIG.Integral()))
        line = line.replace("DYRATE",str(histYieldDY.Integral()))
        line = line.replace("TTRATE",str(histYieldTT.Integral()))
        line = line.replace("ZZRATE",str(histYieldZZ.Integral()))       
        line = line.replace("WZRATE",str(histYieldWZ.Integral()))
        line = line.replace("WWRATE",str(histYieldWW.Integral()))
        datacard.write(line)
        datacard.close()
        return 0.0
    
MakeDataCard("Testing_0819",1,"TemplateDataCard_YJ.txt")
MakeDataCard("Testing_0819",2,"TemplateDataCard_YJ.txt")
MakeDataCard("Testing_0819",3,"TemplateDataCard_YJ.txt")
MakeDataCard("Testing_0819",4,"TemplateDataCard_YJ.txt")
MakeDataCard("Testing_0819",5,"TemplateDataCard_YJ.txt")
MakeShape1dDataCard("Testing_0819","TemplateShape1dDataCard_YJ.txt")
MakeCountingDataCard("Testing_0819","TemplateCountingDataCard_YJ.txt")
