.\StandAlone.exe -i sample.vert > sample.vert.newout 
diff sample.vert.out sample.vert.newout

.\StandAlone.exe -i sample.frag > sample.frag.newout 
diff sample.frag.out sample.frag.newout
