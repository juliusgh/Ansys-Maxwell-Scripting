setup = "HighFidelity"
parameter = "EnergyTransfer"
sweep_property = "charge_coil_turns"
sweep_values = [1,2,3,4,5,6,7,8]
path = "Z:\Transfer\Hbj\Maxwell_Simulationen\C1a"

oProject = oDesktop.GetActiveProject()
oDesign = oProject.GetActiveDesign()

for sweep_value in sweep_values:
    oDesign.SetPropertyValue("LocalVariableTab","LocalVariables",sweep_property,str(sweep_value))
    oDesign.Analyze(setup)
    oModule = oDesign.GetModule("AnalysisSetup")
    oModule.ExportSolnData(setup+" : LastAdaptive", parameter, False, sweep_property+"='"+str(sweep_value)+"'", path+"\sweep-case-"+sweep_property+"-"+str(sweep_value)+"-"+setup+".txt") 