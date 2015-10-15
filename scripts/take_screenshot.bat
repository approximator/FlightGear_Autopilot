
start fgautopilot-0.0.3/fgautopilot.exe

curl -fsS -o nircmd.zip http://www.nirsoft.net/utils/nircmd.zip
7z x nircmd.zip
dir
nircmd.exe cmdwait 20000 savescreenshot "shot.png"
dir
taskkill /f /im "fgautopilot.exe"
