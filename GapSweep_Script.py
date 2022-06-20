setup = "HighFidelity"
parameter = "EnergyTransfer"
sweep_property = "gap"
sweep_values = ['2.0mm','2.5mm','3.0mm','3.5mm','4.0mm','4.5mm','5.0mm']
path = "Z:\Transfer\Hbj\Maxwell_Simulationen\C1a"

oProject = oDesktop.GetActiveProject()
oDesign = oProject.GetActiveDesign()

for sweep_value in sweep_values:
    oDesign.SetPropertyValue("LocalVariableTab","LocalVariables",sweep_property,str(sweep_value))
    oDesign.Analyze(setup)
    oModule = oDesign.GetModule("AnalysisSetup")
    oModule.ExportSolnData(setup+" : LastAdaptive", parameter, False, sweep_property+"='"+str(sweep_value)+"'", path+"\sweep-"+sweep_property+"-"+str(sweep_value)+"-"+setup+".txt") 