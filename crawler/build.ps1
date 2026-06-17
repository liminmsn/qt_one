# 打包输出到 E:\output，临时文件放 temp
pyinstaller `
--clean `
-n img_fetch `
-F -w `
--distpath="./dist" `
--workpath="./temp_build" `
main.py