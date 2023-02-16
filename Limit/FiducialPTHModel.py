from HiggsAnalysis.CombinedLimit.PhysicsModel import *
import re

class FiducialPTH(PhysicsModel):
    def doParametersOfInterest(self):
        """Create POI and other parameters, and define the POI set."""
        self.modelBuilder.doVar("mu_fid[1.0,-15.0,15.0]");
        self.modelBuilder.doVar("rho_0_350[1.0,-25.0,25.0]");
        self.modelBuilder.doVar("rho_350_450[1.0,-25.0,25.0]");
        self.modelBuilder.doVar("rho_450_600[1.0,-25.0,25.0]");
        pois = 'mu_fid,rho_0_350,rho_350_450,rho_450_600'
        self.modelBuilder.doSet("POI",pois)
        if self.options.mass != 0:
            if self.modelBuilder.out.var("MH"):
              self.modelBuilder.out.var("MH").removeRange()
              self.modelBuilder.out.var("MH").setVal(self.options.mass)
            else:
              self.modelBuilder.doVar("MH[%g]" % self.options.mass);
	self.modelBuilder.factory_('expr::scale_0_350("@0*@1",mu_fid,rho_0_350)')
        self.modelBuilder.factory_('expr::scale_350_450("@0*@1",mu_fid,rho_350_450)')
        self.modelBuilder.factory_('expr::scale_450_600("@0*@1",mu_fid,rho_450_600)')
        self.modelBuilder.factory_('expr::scale_GT600("@0*(3.22-@1*1.01-@2*1.36-@3*0.62)/0.23",mu_fid,rho_0_350,rho_350_450,rho_450_600)')

    def getYieldScale(self,bin,process):
        "Return the name of a RooAbsReal to scale this yield by or the two special values 1 and 0 (don't scale, and set to zero)"
        if re.search("PTH_0_350",process):
           return "scale_0_350"
        if re.search("PTH_350_450",process):
           return "scale_350_450"
        if re.search("PTH_450_600",process):
           return "scale_450_600"
        if re.search("PTH_GT600",process):
           return "scale_GT600"
        return 1

fiducialPTH = FiducialPTH()
