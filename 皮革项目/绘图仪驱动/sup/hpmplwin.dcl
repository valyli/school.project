// Next available MSG number is   181 
// MODULE_ID HPMPLWIN_DCL_
hpmainmenu: dialog {
    label = "HP 绘图仪配置";
    alignment = centered;
    initial_focus = "accept";
    : boxed_row {
        key=  "modellabel";
        label = "当前设备配置:";
                :text {
                    key=  "idmodel";
                }
                : button {
                    label = "示意...";
                    key = "DevHints";
                    mnemonic = "i";
                    fixed_width = true;
                }
        }

    : boxed_column {
        label = "内存配置: ";
        key =  "MemCfg";
        : row {
            : toggle {
                label = "内存优化使用";
                key = "OptimizeMem";
                mnemonic = "u";
            }
            : concatenation {
                : edit_box {
                    label = "绘图仪内存: ";
                    key = "PlotMem";
                    mnemonic = "m";
                    alignment = right;
                    edit_width = 3;
                    edit_limit = 3;
                }
                : text_part {
                    label = "兆比特";
                    key = "PlotMemUnits";
                }
            }
            : button {
                label = "示意...";
                key = "MemHints";
                mnemonic = "i";
                fixed_width = true;
            }
        }
    }

    : boxed_column {
        label = "打印配置: ";
        key =  "UserCfg";
        : row {
            : column {  // Begin Left Column
                : boxed_radio_column {
                    label = "质量";
                    key   = "qual";
                    : radio_button {
                        label = "高速 \/ 草稿";
                        key = "draft";
                        mnemonic = "F";
                    }
                    : radio_button {
                        label = "普通 \/ 最终";
                        key = "final";
                        mnemonic = "r";
                        value = "1";
                    }
                    : radio_button {
                        label = "最佳 \/ 增强";
                        key = "enhanced";
                        mnemonic = "E";
                    }
                    : radio_button {
                        label = "绘图仪缺省";
                        key = "pldefault";
                        mnemonic = "D";
                    }
                }  // End radio_column (Print Qual) //
            }  // End Left Column
            : column {  // Begin Middle Column
                : edit_box {
                    label = "复制数目: ";
                    mnemonic = "N";
                    key = "copies";
                    edit_width = 2;
                    edit_limit = 2;
                    fixed_width=true;
                }
                : boxed_radio_column {
                    label = "打印颜色";
                    key   = "color_set";
                    : radio_button {
                        label = "颜色";
                        key = "pcolor";
                        mnemonic = "c";
                    }
                    : radio_button {
                        label = "颜色置为灰";
                        key = "pgray";
                        mnemonic = "g";
                    }
                    : radio_button {
                        label = "全部置黑";
                        key = "pblack";
                        mnemonic = "b";
                    }
                } //end of color setting
            }
            : column {  
                // Begin Right Column
                : button {
                    label = "画笔...";
                    mnemonic = "P";
                    key = "penattr";
                }
                : button {
                    label = "注释...";
                    mnemonic = "A";
                    key = "annotate";
                }
                : button {
                    label = "介质方向...";
                    mnemonic = "O";
                    key = "paper";
                }
                : button {
                    label = "高级介质选项...";
                    mnemonic = "v";
                    key = "advopt";
                }
            }  // End Right Column
        }  // End Row of two columns

    } // End "User config

    : row {
        fixed_width = true;
        alignment = centered;
        : button {
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            key = "helpmain";
            mnemonic = "H";
            width = 12;
        }
        : spacer {
            width = 2;
        }
        : button {
            label = "关于...";
            key = "about";
            mnemonic = "A";
            width = 12;
        }
    }
}  // End MAIN MENU Dialog //

//      PENATTR.DCL
//      Dialog Box for setting attributes for pens
//
penattr: dialog {
    label = "画笔";
    initial_focus = "accept";
    fixed_height = true;
    : row {  // Pen
        : column {
            : popup_list {
                label = "画笔 (1..255): ";
                mnemonic = "P";
                fixed_width = true;
                key = "slider";
                edit_width = 4;
            }
            : button {
                label = "用于全部画笔";
                mnemonic = "A";
                key = "okall";
            }
        }  // End Pen Column
        : column {
            : boxed_row {
                label = "打印合并控制";
                : radio_column {  // Merge
                    key = "mc";
                    fixed_height = true;
                    : radio_button {
                        label = "直线改写";
                        key = "mc0";
                        mnemonic = "O";
                    }
                    : radio_button {
                        label = "直线合并";
                        key = "mc1";
                        mnemonic = "M";
                    }
                }  // End (Merge) column
                : column {
                    fixed_width = true;
                    //fixed_height = true;
                    :image {
                        key = "overw_im";
                        height = 1;
                        aspect_ratio = 1.4;
                    }
                    :image {
                        key = "merge_im";
                        height = 1;
                        aspect_ratio = 1.4;
                    }
                }
                spacer_1;
            } //end merge row
            : button {
                label = "半色调...";
                key = "printop";
                mnemonic = "t";
            }
        }
    }

    : row {
        :boxed_row {
            label = "直线端点: ";
            key = "endlabel";
            mnemonic = "E";
            : image_button {
                key = "end_tile1";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "end_tile2";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "end_tile3";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "end_tile4";
                width = 5;
                aspect_ratio = 0.75;
            }
        }
        :boxed_row {
            label = "直线合并: ";
            key = "joinlabel";
            mnemonic = "J";
            : image_button {
                key = "join_tile1";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile2";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile3";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile4";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile5";
                width = 5;
                aspect_ratio = 0.75;
            }
        }
    }  // End Row (Line ends/joins)

    : row { // ( Fills & Raster patterns)
        : boxed_column {  // Fills
            label = "填充: ";
            mnemonic = "F";
            : list_box {
                fixed_height = true;
                height = 5;
                key = "filltype";
            }
            : edit_box {
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "间距 1..99毫米: ";
                key   = "spacing";
                mnemonic = "S";
            }

            : edit_box {
                fixed_width = true;
                edit_width = 3;
                edit_limit = 3;
                label = "角度 0..359: ";
                key   = "angle";
                mnemonic = "g";
            }

            : edit_box {  // Shade
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "着色 0..99%: ";
                key   = "shdpct";
                mnemonic = "d";
            }  // End Shade
        }  // End column (Fills)

        : boxed_column { // Raster patterns
            label = "光栅图案: ";
            key = "rastpat";
            mnemonic = "R";
            fixed_height = true;
            width = 33;
            : list_box {
                fixed_height = true;
                height = 8;
                key = "patlist";
            }
            : button {
                label = "修改...";
                mnemonic = "C";
                key = "changerast";
            }
        }  // End Column ( Raster Patterns )
    }  // End Row

    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            key = "helppen";
            width = 12;
            mnemonic = "H";
        }
    }

}  // End LINE ATTRIBUTES Dialog //

//      PENPPENATTR.DCL
//      Dialog Box for setting attributes for pens
//
penppenattr: dialog {
    label = "画笔";
    initial_focus = "accept";
    fixed_height = true;
    : row {  // Pen
        : column {
            : popup_list {
                label = "画笔 (1..255): ";
                mnemonic = "P";
                fixed_width = true;
                key = "slider";
                edit_width = 4;
            }
            : button {
                label = "用于全部画笔";
                mnemonic = "A";
                key = "okall";
            }
        }  // End Pen Column
        : column {
            : boxed_row {
                label = "产生区域填充于: ";
                : radio_column {  // SFILLS
                    key = "sfills";
                    fixed_height = true;
                    : radio_button {
                        label = "绘图仪 (最佳锁住时间)";
                        key = "sfillspl";
                        mnemonic = "l";
                    }
                    : radio_button {
                        label = "Arch (最佳绘图时间)";
                        key = "sfillsacad";
                        mnemonic = "D";
                    }
                }  // End (Merge) column
            } //end merge row
        }
    }

    : row {
        :boxed_row {
            label = "直线端点: ";
            key = "endlabel";
            : image_button {
                key = "end_tile1";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "end_tile2";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "end_tile3";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "end_tile4";
                width = 5;
                aspect_ratio = 0.75;
            }
        }
        :boxed_row {
            label = "直线合并: ";
            key = "joinlabel";
            : image_button {
                key = "join_tile1";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile2";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile3";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile4";
                width = 5;
                aspect_ratio = 0.75;
            }
            : image_button {
                key = "join_tile5";
                width = 5;
                aspect_ratio = 0.75;
            }
        }
    }  // End Row (Line ends/joins)

    : row { // ( Fills & Raster patterns)
        key = "fillsdef";
        : boxed_column {  // Fills
            label = "填充: ";
            : list_box {
                fixed_height = true;
                height = 5;
                key = "filltype";
            }
            : edit_box {
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "间距 1..99毫米: ";
                key   = "spacing";
                mnemonic = "S";
            }

            : edit_box {
                fixed_width = true;
                edit_width = 3;
                edit_limit = 3;
                label = "角度 0..359: ";
                key   = "angle";
                mnemonic = "g";
            }

            : edit_box {  // Shade
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "着色 0..99%: ";
                key   = "shdpct";
                mnemonic = "h";
            }  // End Shade
        }  // End column (Fills)

        : boxed_column { // Raster patterns
            key = "rastpat";
            label = "光栅图案: ";
            fixed_height = true;
            width = 33;
            : list_box {
                fixed_height = true;
                height = 8;
                key = "patlist";
            }
            : button {
                label = "修改...";
                mnemonic = "C";
                key = "changerast";
            }
        }  // End Column ( Raster Patterns )
    }  // End Row

    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            key = "helppen";
            width = 12;
            mnemonic = "H";
        }
    }

}  // End LINE ATTRIBUTES Dialog //

//  ANNOTATE.DCL
//  Menu for annotating plot-time variables into left side of plot
//

annotate: dialog {
    label = "注释";
    initial_focus = "accept";
    : row  { // of two columns
        : column {
            : toggle {
                label = "图形文件名";
                key = "dwgname";
                mnemonic = "F";
            }
            : toggle {
                label = "打印日期/时间";
                key = "plottime";
                mnemonic = "T";
            }
        }  // End column (dwgname, plottime)
        : column {
            : toggle {
                label = "驱动程序信息";
                key = "dvrname";
                mnemonic = "I";
            }
            : toggle {
                label = "修剪标记";
                key = "cropmarks";
                mnemonic = "M";
            }
        }  // End column ( drvname, cropmarks )
    }  // End row of 2 columns

    : column {
        : text {
            key = "commentlabel";
            label = "注释: (最多 50 个字符)";
            mnemonic = "C";
        }
        : edit_box {
            key = "comment";
            width = 51;
            edit_limit = 50;
        }
    }  // End Comment column

    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            key = "helpanno";
            mnemonic = "H";
            width = 12;
        }
    }

}  // End PLOT ANNOTATE Dialog //


//  HELP DIALOG
//  The help dialog is popped up to display a help message based
//  on which "screen" the user was interacting with when he
//  depressed the help button

help: dialog {
    label = "帮助/信息";
    initial_focus = "accept";
    : list_box {
        width = 55;
        height = 16;
        key = "helplist";
    }
    : retirement_button {
        label = "确认";
        key = "accept";
        is_default = true;
        is_cancel = true;
    }
}  // End HELP Dialog

//  OKALLPENS DIALOG
okallpens: dialog {
    fixed_width = true;
    alignment = centered;
    label = "!! 注意 !!";
    initial_focus = "accept";
    : text {
        label = "是否“确认”将设置应用全部画笔?";
        key = "askok";
    }
    : row {
        alignment = centered;
        : retirement_button {
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
    }  // End row
}  // End OKALLPENS Dialog //

GenericOrient : dialog {
    label = "介质选项";
    initial_focus = "accept";
    : boxed_row {
        label = "为图象和介质点取“匹配”";
        mnemonic = "C";
        fixed_width = true;
        fixed_height = true;
        spacer_0;
        : column {
            fixed_width = true;
            fixed_height = true;
            : image_button {
                key = "image1";
                width = 14;
                aspect_ratio = 0.65;
            }
            : image_button {
                key = "image3";
                width = 14;
                aspect_ratio =0.65;
            }
            : image_button {
                key = "image5";
                width = 14;
                aspect_ratio =0.65;
            }
            : image_button {
                key = "image7";
                width = 14;
                aspect_ratio = 0.65;
            }
        }
        spacer_0;
        : column {
            fixed_width = true;
            fixed_height = true;
            : image_button {
                key = "image2";
                width = 14;
                aspect_ratio = 0.65;
            }
            : image_button {
                key = "image4";
                width = 14;
                aspect_ratio = 0.65;
            }
            : image_button {
                key = "image6";
                width = 14;
                aspect_ratio = 0.65;
            }
            : image_button {
                key = "image8";
                width = 14;
                aspect_ratio = 0.65;
            }
        }
        spacer_0;
    }
    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {   
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            mnemonic = "H";
            key = "helppaper";
        }
    }  // End Row;
}


BandingOrient : dialog {
    label = "介质选项";
    initial_focus = "accept";
    : boxed_row {
        label = "为图象和介质点取“匹配”";
        mnemonic = "C";
        fixed_width = true;
        fixed_height = true;
        spacer_0;
        : column {
            fixed_width = true;
            fixed_height = true;
            : image_button {
                key = "image1";
                width = 14;
                aspect_ratio = 0.65;
            }
            : image_button {
                key = "image7";
                width = 14;
                aspect_ratio = 0.65;
            }
        }
        spacer_0;
        : column {
            fixed_width = true;
            fixed_height = true;
            : image_button {
                key = "image6";
                width = 14;
                aspect_ratio = 0.65;
            }
            : image_button {
                key = "image8";
                width = 14;
                aspect_ratio = 0.65;
            }
        }
        spacer_0;
    }
    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {   
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            mnemonic = "H";
            key = "helppaper";
        }
    }  // End Row;
}


paperadv : dialog {
    label = "高级介质选项";
    initial_focus = "accept";
    : boxed_row {
        label = "为绘图仪边距选择控制层";
        : boxed_radio_column {
            label = "如果按图纸空间调整是“关闭”";
            key = "sclmarginadj";
            : radio_button {
                label = "显示剪裁警告";
                key = "sclwarnings";
                mnemonic = "w";
            }
            : radio_button {
                label = "不显示警告";
                key = "scldisabled";
                mnemonic = "D";
            }
        }
        : boxed_radio_column {
            label = "如果按图纸空间调整是“打开”";
            key = "marginadj";
            : radio_button {
                label = "不要剪裁。调整到介质";
                key = "adjust";
                mnemonic = "A";
            }
            : radio_button {
                label = "显示剪裁警告";
                key = "warnings";
                mnemonic = "w";
            }
            : radio_button {
                label = "不显示警告";
                key = "disabled";
                mnemonic = "D";
            }
        }
    }
    : boxed_column {
        label = "绘图仪机边距";
        : radio_row {
            key = "expand";
            : radio_button {
                label = "展开“关”";
                key = "expoff";
                mnemonic = "F";
            }
            : radio_button {
                label = "展开“开”";
                key = "expon";
                mnemonic = "N";
            }
        }
        : text {
            label = "必须符合绘图仪设置";
        }
    }
    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {   
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            mnemonic = "H";
            key = "helpadv";
        }
    }  // End Row;
    : text {
        key = "errortext";
        width = 55;
    }
}

printops : dialog {
    label = "半色调";
    initial_focus = "accept";
    : text {
        centered = true;
        label = "(只用于矢量)";
    }
    : row {
        : radio_column {
            key = "dither";
            : radio_button {
                label = "散布图";
                key = "scatter";
                mnemonic = "S";
            }
            : radio_button {
                label = "图案";
                key = "pattern";
                mnemonic = "P";
            }
            : radio_button {
                label = "绘图仪缺省";
                key = "default";
                mnemonic = "d";
            }
        }
        : column {
            fixed_width = true;
            fixed_height = true;
            : image {
                key = "sc_im";
                height = 1;
                aspect_ratio = 6;
            }
            : image {
                key = "pt_im";
                height = 1;
                aspect_ratio = 6;
            }
            spacer_1;
        }
    }
    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {   
            label = "确认";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "取消";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "帮助...";
            mnemonic = "H";
            key = "helpprintop";
        }
    }  // End Row;
}

aboutmsg : dialog {
    label = "关于";
    width  = 64;
    : text {
        key = "DriverVersion";
        alignment = centered;
    }
    : text {
        key = "AboutHeaderKey";
        alignment = centered;
    }
    : list_box {
        fixed_height = true;
        height = 12;
        key =  "AboutKey";
    }
    : button {
        label = "确认";
        key = "accept";
        fixed_width = true;
        alignment = centered;
        width = 12;
        is_default = true;
    }
}
