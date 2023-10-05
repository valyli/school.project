// Next available MSG number is   181 
// MODULE_ID HPMPLWIN_DCL_
hpmainmenu: dialog {
    label = "HP ��ͼ������";
    alignment = centered;
    initial_focus = "accept";
    : boxed_row {
        key=  "modellabel";
        label = "��ǰ�豸����:";
                :text {
                    key=  "idmodel";
                }
                : button {
                    label = "ʾ��...";
                    key = "DevHints";
                    mnemonic = "i";
                    fixed_width = true;
                }
        }

    : boxed_column {
        label = "�ڴ�����: ";
        key =  "MemCfg";
        : row {
            : toggle {
                label = "�ڴ��Ż�ʹ��";
                key = "OptimizeMem";
                mnemonic = "u";
            }
            : concatenation {
                : edit_box {
                    label = "��ͼ���ڴ�: ";
                    key = "PlotMem";
                    mnemonic = "m";
                    alignment = right;
                    edit_width = 3;
                    edit_limit = 3;
                }
                : text_part {
                    label = "�ױ���";
                    key = "PlotMemUnits";
                }
            }
            : button {
                label = "ʾ��...";
                key = "MemHints";
                mnemonic = "i";
                fixed_width = true;
            }
        }
    }

    : boxed_column {
        label = "��ӡ����: ";
        key =  "UserCfg";
        : row {
            : column {  // Begin Left Column
                : boxed_radio_column {
                    label = "����";
                    key   = "qual";
                    : radio_button {
                        label = "���� \/ �ݸ�";
                        key = "draft";
                        mnemonic = "F";
                    }
                    : radio_button {
                        label = "��ͨ \/ ����";
                        key = "final";
                        mnemonic = "r";
                        value = "1";
                    }
                    : radio_button {
                        label = "��� \/ ��ǿ";
                        key = "enhanced";
                        mnemonic = "E";
                    }
                    : radio_button {
                        label = "��ͼ��ȱʡ";
                        key = "pldefault";
                        mnemonic = "D";
                    }
                }  // End radio_column (Print Qual) //
            }  // End Left Column
            : column {  // Begin Middle Column
                : edit_box {
                    label = "������Ŀ: ";
                    mnemonic = "N";
                    key = "copies";
                    edit_width = 2;
                    edit_limit = 2;
                    fixed_width=true;
                }
                : boxed_radio_column {
                    label = "��ӡ��ɫ";
                    key   = "color_set";
                    : radio_button {
                        label = "��ɫ";
                        key = "pcolor";
                        mnemonic = "c";
                    }
                    : radio_button {
                        label = "��ɫ��Ϊ��";
                        key = "pgray";
                        mnemonic = "g";
                    }
                    : radio_button {
                        label = "ȫ���ú�";
                        key = "pblack";
                        mnemonic = "b";
                    }
                } //end of color setting
            }
            : column {  
                // Begin Right Column
                : button {
                    label = "����...";
                    mnemonic = "P";
                    key = "penattr";
                }
                : button {
                    label = "ע��...";
                    mnemonic = "A";
                    key = "annotate";
                }
                : button {
                    label = "���ʷ���...";
                    mnemonic = "O";
                    key = "paper";
                }
                : button {
                    label = "�߼�����ѡ��...";
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
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
            key = "helpmain";
            mnemonic = "H";
            width = 12;
        }
        : spacer {
            width = 2;
        }
        : button {
            label = "����...";
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
    label = "����";
    initial_focus = "accept";
    fixed_height = true;
    : row {  // Pen
        : column {
            : popup_list {
                label = "���� (1..255): ";
                mnemonic = "P";
                fixed_width = true;
                key = "slider";
                edit_width = 4;
            }
            : button {
                label = "����ȫ������";
                mnemonic = "A";
                key = "okall";
            }
        }  // End Pen Column
        : column {
            : boxed_row {
                label = "��ӡ�ϲ�����";
                : radio_column {  // Merge
                    key = "mc";
                    fixed_height = true;
                    : radio_button {
                        label = "ֱ�߸�д";
                        key = "mc0";
                        mnemonic = "O";
                    }
                    : radio_button {
                        label = "ֱ�ߺϲ�";
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
                label = "��ɫ��...";
                key = "printop";
                mnemonic = "t";
            }
        }
    }

    : row {
        :boxed_row {
            label = "ֱ�߶˵�: ";
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
            label = "ֱ�ߺϲ�: ";
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
            label = "���: ";
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
                label = "��� 1..99����: ";
                key   = "spacing";
                mnemonic = "S";
            }

            : edit_box {
                fixed_width = true;
                edit_width = 3;
                edit_limit = 3;
                label = "�Ƕ� 0..359: ";
                key   = "angle";
                mnemonic = "g";
            }

            : edit_box {  // Shade
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "��ɫ 0..99%: ";
                key   = "shdpct";
                mnemonic = "d";
            }  // End Shade
        }  // End column (Fills)

        : boxed_column { // Raster patterns
            label = "��դͼ��: ";
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
                label = "�޸�...";
                mnemonic = "C";
                key = "changerast";
            }
        }  // End Column ( Raster Patterns )
    }  // End Row

    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
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
    label = "����";
    initial_focus = "accept";
    fixed_height = true;
    : row {  // Pen
        : column {
            : popup_list {
                label = "���� (1..255): ";
                mnemonic = "P";
                fixed_width = true;
                key = "slider";
                edit_width = 4;
            }
            : button {
                label = "����ȫ������";
                mnemonic = "A";
                key = "okall";
            }
        }  // End Pen Column
        : column {
            : boxed_row {
                label = "�������������: ";
                : radio_column {  // SFILLS
                    key = "sfills";
                    fixed_height = true;
                    : radio_button {
                        label = "��ͼ�� (�����סʱ��)";
                        key = "sfillspl";
                        mnemonic = "l";
                    }
                    : radio_button {
                        label = "Arch (��ѻ�ͼʱ��)";
                        key = "sfillsacad";
                        mnemonic = "D";
                    }
                }  // End (Merge) column
            } //end merge row
        }
    }

    : row {
        :boxed_row {
            label = "ֱ�߶˵�: ";
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
            label = "ֱ�ߺϲ�: ";
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
            label = "���: ";
            : list_box {
                fixed_height = true;
                height = 5;
                key = "filltype";
            }
            : edit_box {
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "��� 1..99����: ";
                key   = "spacing";
                mnemonic = "S";
            }

            : edit_box {
                fixed_width = true;
                edit_width = 3;
                edit_limit = 3;
                label = "�Ƕ� 0..359: ";
                key   = "angle";
                mnemonic = "g";
            }

            : edit_box {  // Shade
                fixed_width = true;
                edit_width = 2;
                edit_limit = 2;
                label = "��ɫ 0..99%: ";
                key   = "shdpct";
                mnemonic = "h";
            }  // End Shade
        }  // End column (Fills)

        : boxed_column { // Raster patterns
            key = "rastpat";
            label = "��դͼ��: ";
            fixed_height = true;
            width = 33;
            : list_box {
                fixed_height = true;
                height = 8;
                key = "patlist";
            }
            : button {
                label = "�޸�...";
                mnemonic = "C";
                key = "changerast";
            }
        }  // End Column ( Raster Patterns )
    }  // End Row

    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
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
    label = "ע��";
    initial_focus = "accept";
    : row  { // of two columns
        : column {
            : toggle {
                label = "ͼ���ļ���";
                key = "dwgname";
                mnemonic = "F";
            }
            : toggle {
                label = "��ӡ����/ʱ��";
                key = "plottime";
                mnemonic = "T";
            }
        }  // End column (dwgname, plottime)
        : column {
            : toggle {
                label = "����������Ϣ";
                key = "dvrname";
                mnemonic = "I";
            }
            : toggle {
                label = "�޼����";
                key = "cropmarks";
                mnemonic = "M";
            }
        }  // End column ( drvname, cropmarks )
    }  // End row of 2 columns

    : column {
        : text {
            key = "commentlabel";
            label = "ע��: (��� 50 ���ַ�)";
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
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
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
    label = "����/��Ϣ";
    initial_focus = "accept";
    : list_box {
        width = 55;
        height = 16;
        key = "helplist";
    }
    : retirement_button {
        label = "ȷ��";
        key = "accept";
        is_default = true;
        is_cancel = true;
    }
}  // End HELP Dialog

//  OKALLPENS DIALOG
okallpens: dialog {
    fixed_width = true;
    alignment = centered;
    label = "!! ע�� !!";
    initial_focus = "accept";
    : text {
        label = "�Ƿ�ȷ�ϡ�������Ӧ��ȫ������?";
        key = "askok";
    }
    : row {
        alignment = centered;
        : retirement_button {
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
    }  // End row
}  // End OKALLPENS Dialog //

GenericOrient : dialog {
    label = "����ѡ��";
    initial_focus = "accept";
    : boxed_row {
        label = "Ϊͼ��ͽ��ʵ�ȡ��ƥ�䡱";
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
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
            mnemonic = "H";
            key = "helppaper";
        }
    }  // End Row;
}


BandingOrient : dialog {
    label = "����ѡ��";
    initial_focus = "accept";
    : boxed_row {
        label = "Ϊͼ��ͽ��ʵ�ȡ��ƥ�䡱";
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
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
            mnemonic = "H";
            key = "helppaper";
        }
    }  // End Row;
}


paperadv : dialog {
    label = "�߼�����ѡ��";
    initial_focus = "accept";
    : boxed_row {
        label = "Ϊ��ͼ�Ǳ߾�ѡ����Ʋ�";
        : boxed_radio_column {
            label = "�����ͼֽ�ռ�����ǡ��رա�";
            key = "sclmarginadj";
            : radio_button {
                label = "��ʾ���þ���";
                key = "sclwarnings";
                mnemonic = "w";
            }
            : radio_button {
                label = "����ʾ����";
                key = "scldisabled";
                mnemonic = "D";
            }
        }
        : boxed_radio_column {
            label = "�����ͼֽ�ռ�����ǡ��򿪡�";
            key = "marginadj";
            : radio_button {
                label = "��Ҫ���á�����������";
                key = "adjust";
                mnemonic = "A";
            }
            : radio_button {
                label = "��ʾ���þ���";
                key = "warnings";
                mnemonic = "w";
            }
            : radio_button {
                label = "����ʾ����";
                key = "disabled";
                mnemonic = "D";
            }
        }
    }
    : boxed_column {
        label = "��ͼ�ǻ��߾�";
        : radio_row {
            key = "expand";
            : radio_button {
                label = "չ�����ء�";
                key = "expoff";
                mnemonic = "F";
            }
            : radio_button {
                label = "չ��������";
                key = "expon";
                mnemonic = "N";
            }
        }
        : text {
            label = "������ϻ�ͼ������";
        }
    }
    : row {
        fixed_width = true;
        alignment = centered;
        : retirement_button {   
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
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
    label = "��ɫ��";
    initial_focus = "accept";
    : text {
        centered = true;
        label = "(ֻ����ʸ��)";
    }
    : row {
        : radio_column {
            key = "dither";
            : radio_button {
                label = "ɢ��ͼ";
                key = "scatter";
                mnemonic = "S";
            }
            : radio_button {
                label = "ͼ��";
                key = "pattern";
                mnemonic = "P";
            }
            : radio_button {
                label = "��ͼ��ȱʡ";
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
            label = "ȷ��";
            key = "accept";
            width = 12;
            is_default = true;
        }
        : retirement_button {
            label = "ȡ��";
            key = "cancel";
            width = 12;
            is_cancel = true;
        }
        : button {
            label = "����...";
            mnemonic = "H";
            key = "helpprintop";
        }
    }  // End Row;
}

aboutmsg : dialog {
    label = "����";
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
        label = "ȷ��";
        key = "accept";
        fixed_width = true;
        alignment = centered;
        width = 12;
        is_default = true;
    }
}
