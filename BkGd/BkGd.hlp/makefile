

BkGd.chm : *.htm BkGd.hhp BkGd.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" BkGd


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F BkGd.chm


Release/BkGd.chm : BkGd.chm
  copy $(MAKEDIR)\BkGd.chm  $(MAKEDIR)\..\Release\BkGd.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del BkGd.chm
  cd $(MAKEDIR)


Debug/BkGd.chm : BkGd.chm
  copy $(MAKEDIR)\BkGd.chm  $(MAKEDIR)\..\Debug\BkGd.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del BkGd.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/BkGd.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/BkGd.chm


