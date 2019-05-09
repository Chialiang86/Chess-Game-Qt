#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),block_width(75),frame_width(600),edit_width(40),dead_width(20) {
    ui->setupUi(this);
    resize(1000,700);
    setWindowTitle("- CHESS的啦 -");

    setMouseTracking(true);

    //set gmae background
    background = new QLabel(this);
    QPixmap bg(":/img/src/ImageSet/background1.png");
    background->setGeometry(0,0,1600,1000);
    background->setPixmap(bg);
    background->setAlignment(Qt::AlignCenter);
    background->setPixmap(bg.scaled(1600,1000,Qt::KeepAspectRatioByExpanding));
    background->show();

    //set board background
    board_table = new QLabel(this);
    QPixmap bt(":/img/src/ImageSet/background2.png");
    board_table->setGeometry(40,40,620,620);
    board_table->setPixmap(bt);
    board_table->setAlignment(Qt::AlignCenter);
    board_table->setPixmap(bt.scaled(620,620,Qt::KeepAspectRatio));
    board_table->show();//start ctrl

    //set position array
    for(int i=0; i<8; ++i) {
        board_xpos[i]=50+i*block_width;
        board_ypos[i]=50+i*block_width;
    }

    //set edit pos
    for(int i = 0 ; i < 8 ; ++ i){
        edit_xpos[i] = 670 + i * edit_width;
    }
    //group 0 (670:990,340:420)
    edit_ypos[0] = 340;
    edit_ypos[1] = 380;
    //group 0 (670:990,420:500)
    edit_ypos[2] = 460;
    edit_ypos[3] = 420;


    //text info
    text.setColor(QPalette::WindowText,QColor(0,0,0));
    //set dead info
    dead_text[0] = new QLabel(this);
    dead_text[0]->setGeometry(730,600,200,30);
    dead_text[0]->setAlignment(Qt::AlignCenter);
    dead_text[0]->setText("BLACK DEAD PIECES");
    dead_text[0]->setFont(QFont("Fantasy",14));
    dead_text[0]->setPalette(text);
    dead_text[0]->show();
    dead_text[1] = new QLabel(this);
    dead_text[1]->setGeometry(730,540,200,30);
    dead_text[1]->setAlignment(Qt::AlignCenter);
    dead_text[1]->setText("WHITE DEAD PIECES");
    dead_text[1]->setFont(QFont("Fantasy",14));
    dead_text[1]->setPalette(text);
    dead_text[1]->show();

    for(int i=0; i<16; ++i)
        dead_xpos[i]=670+i*dead_width;
    dead_ypos[0]=630;
    dead_ypos[1]=570;
    dead_count[0]=0;
    dead_count[1]=0;

    //set board background
    QPixmap block_color[2];
    block_color[0].load(":/img/src/ImageSet/board_b.png");
    block_color[1].load(":/img/src/ImageSet/board_w.png");
    for(int i=0; i<DIMENSION_X; ++i) {
        for(int j=0; j<DIMENSION_Y; ++j) {
            checkerboard[i][j]=new QLabel(this);
            checkerboard[i][j]->setGeometry(board_xpos[i],board_ypos[j],block_width,block_width);
            checkerboard[i][j]->setAlignment(Qt::AlignCenter);
            checkerboard[i][j]->setPixmap(block_color[(i+j)%2].scaled(block_width,block_width,Qt::KeepAspectRatioByExpanding));
            checkerboard[i][j]->show();//start ctrl
        }
    }

    //set logo & game img
    game=new QLabel(this);
    game_img.load(":/img/src/ImageSet/game_img.png");
    game->setGeometry(730,20,200,200);
    game->setPixmap(game_img.scaled(200,200,Qt::IgnoreAspectRatio));
    game->show();
    logo=new QLabel(this);
    logo_img.load(":/img/src/ImageSet/logo.png");
    logo->setGeometry(690,120,280,70);
    logo->setAlignment(Qt::AlignCenter);
    logo->setPixmap(logo_img.scaled(280,70,Qt::IgnoreAspectRatio));
    logo->show();

    //button palette
    button.setColor(QPalette::Button,QColor(60,60,60));
    button.setColor(QPalette::ButtonText,QColor(150,235,255));

    //set pushbutton
    start_ctrl=new QPushButton(this);
    start_ctrl->setGeometry(755,250,150,50);
    start_ctrl->setText("START");
    start_ctrl->setFont(QFont("Fantasy",20));
    start_ctrl->setAutoFillBackground(true);
    start_ctrl->setPalette(button);
    start_ctrl->show();

    undo=new QPushButton(this);
    undo->setGeometry(755,330,150,50);
    undo->setText("UNDO");
    undo->setFont(QFont("Fantasy",20));
    undo->setAutoFillBackground(true);
    undo->setPalette(button);
    undo->show();

    edit_ctrl=new QPushButton(this);
    edit_ctrl->setGeometry(755,410,150,50);
    edit_ctrl->setText("EDIT");
    edit_ctrl->setFont(QFont("Fantasy",20));
    edit_ctrl->setAutoFillBackground(true);
    edit_ctrl->setPalette(button);
    edit_ctrl->show();

    //edit_ctrl set
    on = new onlineplay(nullptr);
    on->close();

    //set sount
    put_sound = new QMediaPlayer(this);
    put_sound->setMedia(QUrl("qrc:/sound/src/sound/put_sound.mp3"));
    put_sound->setVolume(10);

    check_sound[0] = new QMediaPlayer(this);
    check_sound[0]->setMedia(QUrl("qrc:/sound/src/sound/black_check_sound.mp3"));
    check_sound[0]->setVolume(15);
    check_sound[1] = new QMediaPlayer(this);
    check_sound[1]->setMedia(QUrl("qrc:/sound/src/sound/white_check_sound.mp3"));
    check_sound[1]->setVolume(15);

    win_sound[0] = new QMediaPlayer(this);
    win_sound[0]->setMedia(QUrl("qrc:/sound/src/sound/black_win_sound.mp3"));
    win_sound[0]->setVolume(20);
    win_sound[1] = new QMediaPlayer(this);
    win_sound[1]->setMedia(QUrl("qrc:/sound/src/sound/white_win_sound.mp3"));
    win_sound[1]->setVolume(20);

    dead = new QMediaPlayer(this);
    dead->setMedia(QUrl("qrc:/sound/src/sound/dead.mp3"));
    dead->setVolume(30);

    //debug
    connect(put_sound, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),
        [=](QMediaPlayer::Error error){
        switch(error){
        case QMediaPlayer::NoError: cout<<"good\n"; break;
        case QMediaPlayer::ResourceError: cout<<"src bad\n"; break;
        case QMediaPlayer::FormatError: cout<<"fmt bad\n"; break;
        case QMediaPlayer::ServiceMissingError: cout<<"service bad\n"; break;
        default: cout<<"other\n"; break;
        }
    });

    //set board info
    b_color[0].load(":/pureColor/src/pureColor/orange.png");
    b_color[1].load(":/pureColor/src/pureColor/green.png");
    b_color[2].load(":/pureColor/src/pureColor/red.png");

    for(int x=0; x<8; ++x)
        for(int y=0; y<8; ++y){
            board[x][y].xindex = x;
            board[x][y].yindex = y;
            board[x][y].color=new QLabel(this);
            board[x][y].color->setGeometry(board_xpos[x]+5,board_ypos[y]+5,block_width-10,block_width-10);
            board[x][y].color->setPixmap(b_color[1].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
            board[x][y].color->close();
        }

    //pawn
    piece[0][pawn].load(":/chess-pieces/src/chesspiece/90px-Chess_pdt45.svg.png");
    piece[1][pawn].load(":/chess-pieces/src/chesspiece/90px-Chess_plt45.svg.png");

    //rook img
    piece[0][rook].load(":/chess-pieces/src/chesspiece/90px-Chess_rdt45.svg.png");
    piece[1][rook].load(":/chess-pieces/src/chesspiece/90px-Chess_rlt45.svg.png");

    //knight img
    piece[0][knight].load(":/chess-pieces/src/chesspiece/90px-Chess_ndt45.svg.png");
    piece[1][knight].load(":/chess-pieces/src/chesspiece/90px-Chess_nlt45.svg.png");

    //bishop
    piece[0][bishop].load(":/chess-pieces/src/chesspiece/90px-Chess_bdt45.svg.png");
    piece[1][bishop].load(":/chess-pieces/src/chesspiece/90px-Chess_blt45.svg.png");

    //queen king
    piece[0][queen].load(":/chess-pieces/src/chesspiece/90px-Chess_qdt45.svg.png");
    piece[1][queen].load(":/chess-pieces/src/chesspiece/90px-Chess_qlt45.svg.png");
    piece[0][king].load(":/chess-pieces/src/chesspiece/90px-Chess_kdt45.svg.png");
    piece[1][king].load(":/chess-pieces/src/chesspiece/90px-Chess_klt45.svg.png");

    piece_id temp_id;
    for(int group = 0 ; group < 2 ; ++ group)
        for(int chess = 0 ; chess < 16 ; ++ chess){
            chess_pieces[group][chess].img = new QLabel(this);

            //set group
            chess_pieces[group][chess].group = static_cast<bool>(group);

            //set special skill
            if(chess<8||chess==12)
                chess_pieces[group][chess].special_skill=true;
            else {
                chess_pieces[group][chess].special_skill=false;
            }

            //set id
            if(chess<8)
                chess_pieces[group][chess].id=pawn;//pawn
            else if(chess==8||chess==15)
                chess_pieces[group][chess].id=rook;//rook
            else if(chess==9||chess==14)
                chess_pieces[group][chess].id=knight;//knight
            else if(chess==10||chess==13)
                chess_pieces[group][chess].id=bishop;//bishop
            else if(chess==11)
                chess_pieces[group][chess].id=queen;//queen
            else//12
                chess_pieces[group][chess].id=king;//king

            //set id img
            temp_id = chess_pieces[group][chess].id;
            chess_pieces[group][chess].img->setPixmap(piece[group][temp_id].scaled(block_width,block_width,Qt::KeepAspectRatio));
            chess_pieces[group][chess].img->close();
        }

    start = false;
    done = true;
    edit = false;
    edit_move = false;
    edit_group = -1;
    edit_chess = -1;

    game_record=new record_info[MAX_TURN];
    record_index=0;

    //reset();
    connect(edit_ctrl,SIGNAL(clicked()),this,SLOT(edit_set()));
    connect(undo,SIGNAL(clicked()),this,SLOT(undo_set()));
    connect(start_ctrl,SIGNAL(clicked()),this,SLOT(game_start()));
    connect(this,SIGNAL(piece_clicked()),this,SLOT(assign_id_func()));
    connect(this,SIGNAL(route_clicked()),this,SLOT(set_piece()));

    imgLabel = new QLabel(this);
    c = new QCamera(this);
    ic = new QCameraImageCapture(c);
    vf = new QCameraViewfinder(this);
    t = new QTimer(this);

    connect(t,SIGNAL(timeout()),this,SLOT(videoFrameCapture()));
    connect(ic,SIGNAL(imageCaptured(int,QImage)),this,SLOT(displayImage(int,QImage)));

    //設定視訊參數
    //c->start();//開始擷取畫面
    c->setCaptureMode(QCamera::CaptureViewfinder);
    c->setViewfinder(vf);

    //t->start(5000);//每33毫秒觸發displayImage()

}

void MainWindow::cerror(){
    
}

void MainWindow::videoFrameCapture(){

    ic->capture();
}

void MainWindow::displayImage(int id, QImage image){
    id = 0;
    imgLabel->setGeometry(780,500,100,100);
    imgLabel->setPixmap(QPixmap::fromImage(image));
    imgLabel->show();

    ////保存圖片
    //QFilefile("C:/Test/yourFile.png");
    //file.open(QIODevice::WriteOnly);
    //ui->imgLabel->pixmap()->save(&file,"PNG");
}

void MainWindow::game_start(){
    if(!start){
        start=true;
        start_ctrl->setText("RESTART");
        start_ctrl->update();
        reset();
    }
    else{
        reset();
    }
}
void MainWindow::edit_set(){
    if(!edit){
        start_ctrl->hide();
        undo->hide();
        edit_ctrl->setGeometry(755,250,150,50);
        edit_ctrl->setText("END EDIT");
        for(int x=0; x<8; ++x)
            for(int y=0; y<8; ++y){
                board[x][y].group = -1;
                board[x][y].id = none;
                board[x][y].index = -1;
                board[x][y].legal = false;
                board[x][y].color->setGeometry(board_xpos[x]+5,board_ypos[y]+5,block_width-10,block_width-10);
                board[x][y].color->setPixmap(b_color[1].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
                board[x][y].color->close();
            }
        pieces temp;
        int x , y;
        for(int group = 0 ; group < 2 ; ++ group){
            for(int chess = 0 ; chess < 16 ; ++ chess){
                x = chess % 8;
                y = group * 2 + !( chess / 8 ) ;
                chess_pieces[group][chess].x = x;
                chess_pieces[group][chess].y = y;
                chess_pieces[group][chess].alive = false;
                temp = chess_pieces[group][chess];
                chess_pieces[group][chess].img->setGeometry(edit_xpos[x],edit_ypos[y],edit_width,edit_width);
                chess_pieces[group][chess].img->setPixmap(piece[group][temp.id].scaled(edit_width,edit_width));
                chess_pieces[group][chess].img->show();
            }
        }
        edit = true;
        start = false;
    }else{
        start_ctrl->show();
        undo->show();
        edit_ctrl->setGeometry(755,410,150,50);
        edit_ctrl->setText("EDIT");
        dead_count[0] = 0;
        dead_count[1] = 0;
        pieces temp;
        for(int group = 0 ; group < 2 ; ++ group)
            for(short chess = 0 ; chess < 16 ; ++ chess){
                temp = chess_pieces[group][chess];
                if(temp.alive){
                    switch(temp.id){
                    case pawn:
                        if(temp.group)
                            temp.y == 6 ? chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        else
                            temp.y == 1 ? chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        break;
                    case rook:
                        if(temp.group)
                            temp.y == 7 && ((temp.x == 0 &&  chess == 8) || (temp.x ==7 && chess ==15)) ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        else
                            temp.y == 0 && ((temp.x == 0 &&  chess == 8) || (temp.x ==7 && chess ==15)) ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        break;
                    case knight:
                        if(temp.group)
                            temp.y == 7 && (temp.x == 1 || temp.x ==6) ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        else
                            temp.y == 0 && (temp.x == 1 || temp.x ==6) ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        break;
                    case bishop:
                        if(temp.group)
                            temp.y == 7 && (temp.x == 2 || temp.x ==5) ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        else
                            temp.y == 0 && (temp.x == 2 || temp.x ==5) ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        break;
                    case queen:
                        if(temp.group)
                            temp.y == 7 && temp.x == 3  ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        else
                            temp.y == 0 && temp.x == 3  ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        break;
                    case king:
                        if(temp.group)
                            temp.y == 7 && temp.x == 4  ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        else
                            temp.y == 0 && temp.x == 4  ?
                                        chess_pieces[group][chess].first = true : chess_pieces[group][chess].first = false;
                        break;
                    default:
                        cout<<"OMG OMG OMG!!!!!!"<<endl;
                        break;
                    }
                }
                else if(temp.alive == false){
                    set_dead(group,chess);
                }
            }
        edit = false;
        start = true;
    }
}

void MainWindow::reset(){
    //record info initialize
    delete [] game_record;
    game_record=new record_info[MAX_TURN];
    record_index=0;

    for(int x=0; x<8; ++x)
        for(int y=0; y<8; ++y) {
            board[x][y].color->setPixmap(b_color[1].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
            board[x][y].color->close();
            board[x][y].legal=false;
            if(y==1||y==6) {
                board[x][y].id=pawn;
                y==1 ? board[x][y].group=0 : board[x][y].group=1 ;
                board[x][y].index=static_cast<short>(x);
            } else if(y==0||y==7) {
                switch(x) {
                case 0:
                case 7:
                    board[x][y].id=rook;
                    y==0 ? board[x][y].group=0 : board[x][y].group=1 ;
                    board[x][y].index=static_cast<short>(8+x);
                    break;
                case 1:
                case 6:
                    board[x][y].id=knight;
                    y==0 ? board[x][y].group=0 : board[x][y].group=1;
                    board[x][y].index=static_cast<short>(8+x);
                    break;
                case 2:
                case 5:
                    board[x][y].id=bishop;
                    y==0 ? board[x][y].group=0 : board[x][y].group=1;
                    board[x][y].index=static_cast<short>(8+x);
                    break;
                case 3:
                    board[x][y].id=queen;
                    y==0 ? board[x][y].group=0 : board[x][y].group=1;
                    board[x][y].index=static_cast<short>(8+x);
                    break;
                case 4:
                    board[x][y].id=king;
                    y==0 ? board[x][y].group=0 : board[x][y].group=1;
                    board[x][y].index=static_cast<short>(8+x);
                    break;
                }
            } else {
                board[x][y].id=none;
                board[x][y].group=-1;
                board[x][y].index=-1;
            }
        }
    piece_id temp_id;
    for(int group=0; group<2; ++group) {
        for(int chess=0; chess<16; ++chess) {

            //set alive
            chess_pieces[group][chess].alive=true;

            //set first
            chess_pieces[group][chess].first=true;

            //set special skill
            if(chess<8||chess==12)
                chess_pieces[group][chess].special_skill=true;

            //set position
            chess_pieces[group][chess].x = chess % 8;
            chess_pieces[group][chess].y = group * 7 + (-2 * group + 1) * !(chess / 8);
            //cout << chess << " " <<chess_pieces[group][chess].x << " " << chess_pieces[group][chess].y << endl

            if(group)
                chess_pieces[group][chess].img->setGeometry(board_xpos[chess%8],board_ypos[6+chess/8],block_width,block_width);
            else
                chess_pieces[group][chess].img->setGeometry(board_xpos[chess%8],board_ypos[1-chess/8],block_width,block_width);


            temp_id = chess_pieces[group][chess].id;
            chess_pieces[group][chess].img->setPixmap(piece[group][temp_id].scaled(block_width,block_width,Qt::KeepAspectRatio));

            if(start)
                chess_pieces[group][chess].img->show();//start ctrl
            else
                chess_pieces[group][chess].img->close();//restart ctrl
        }
    }
    //reset dead
    dead_count[0]=0;
    dead_count[1]=0;

    //set updown
    up_down = false;

    //clear legal
    reset_route(true);

    //set mouse press
    pturn=1;//white first
    done=true;

}

void MainWindow::reset_route(bool all) {
    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j) {
            if(all)
                board[i][j].color->close();
            board[i][j].legal=false;
        }

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    int x=(event->x()-50)/block_width,
        y=(event->y()-50)/block_width;
    if(start){
        //y = (7 - 2 * y) * up_down + y;

        //reset_route();
        if(done && x < 8 && y < 8 && board[x][y].group == pturn && board[x][y].legal==false) {
            reset_route(true);
            temp=board[x][y];
            emit piece_clicked();
        }else{
            if( done && board[x][y].legal == true && x < 8 && y < 8) { //legal route
                t_info=board[x][y];
                emit route_clicked();
            }
        }
    }
    else if(edit && !edit_move){
        //count chess piece before move
        edit_group = ( event->y() - 340 ) / 80;
        edit_chess = ( event->x() - 670 ) / 40;
        if(event->x() >= 670 && event->x() < 990 && event->y() >= 340 && event->y() < 500){
            if(edit_group){
                if(event->y() >= 460 && event->y() < 500)
                    edit_chess = 8 + edit_chess;
            }
            else {
                if(event->y() >= 340 && event->y() < 380)
                    edit_chess = 8 + edit_chess;
            }
            piece_id temp_id;
            temp_id = chess_pieces[edit_group][edit_chess].id;
            chess_pieces[edit_group][edit_chess].img->setGeometry(event->x() - 30,event->y() - 30,block_width,block_width);
            chess_pieces[edit_group][edit_chess].img->setPixmap(piece[edit_group][temp_id].scaled(block_width,block_width));
            edit_move = true;
        }
        else if(x < 8 && x >= 0 && y < 8 && y >= 0 && board[x][y].id != none){
            board_info temp = board[x][y];
            bool temp_g = temp.group;
            short temp_i = temp.index;
            reset_route(true);
            board[x][y].color->show();
            chess_pieces[temp_g][temp_i].img->setGeometry(event->x() - 30,event->y() - 30,block_width,block_width);
            edit_group = temp_g;
            edit_chess = temp.index;
            edit_move = true;
            board[x][y].group = -1;
            board[x][y].id = none;
            board[x][y].index = -1;
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(edit && edit_move){
        if((edit_group >= 0 || edit_group == 1) && edit_chess >= 0 && edit_chess < 16){
            chess_pieces[edit_group][edit_chess].img->setGeometry(event->x() - 30,event->y() - 30,block_width,block_width);
            chess_pieces[edit_group][edit_chess].img->update();
            int x_=(event->x()-50)/block_width,
                y_=(event->y()-50)/block_width;
            if(x_ >= 0 && x_ < 8 && y_ >= 0 && y_ < 8){
                reset_route(true);
                board[x_][y_].color->show();
            }
        }
    }

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(edit && edit_move){
        int x=(event->x()-50)/block_width,
            y=(event->y()-50)/block_width;
        if(x >= 0 && x < 8 && y >= 0 && y < 8){
            chess_pieces[edit_group][edit_chess].x = x;
            chess_pieces[edit_group][edit_chess].y = y;
            chess_pieces[edit_group][edit_chess].alive = true;
            chess_pieces[edit_group][edit_chess].img->setGeometry(board_xpos[x],board_ypos[y],block_width,block_width);
            board[x][y].group = chess_pieces[edit_group][edit_chess].group;
            board[x][y].id = chess_pieces[edit_group][edit_chess].id;
            board[x][y].index = static_cast<short>(edit_chess);
            reset_route(true);
            put_sound->stop();
            put_sound->play();
        }
        else{
            piece_id temp_id = chess_pieces[edit_group][edit_chess].id;
            int temp_x = chess_pieces[edit_group][edit_chess].x;
            int temp_y = chess_pieces[edit_group][edit_chess].y;
            cout<<"temp_x: "<<temp_x<<"  temp_y: "<<temp_y<<endl;
            chess_pieces[edit_group][edit_chess].img->setGeometry(edit_xpos[temp_x],edit_ypos[temp_y],edit_width,edit_width);
            chess_pieces[edit_group][edit_chess].img->setPixmap(piece[edit_group][temp_id].scaled(edit_width,edit_width));
        }
        edit_chess = -1;
        edit_group = -1;
        edit_move = false;
        debug();
    }
}


void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    x = 0;
    y = 0;
    //reset_route();
    //red->close();
}

void MainWindow::assign_id_func() {
    int temp_x=temp.xindex,
        temp_y=temp.yindex;
    //temp_y=!pturn*(7-2*temp_y)+temp_y;
    bool g;
    bool first;
    if(temp.group != -1){
        g=chess_pieces[temp.group][temp.index].group;
        first=chess_pieces[temp.group][temp.index].first;
        switch(temp.id) {
        case pawn :
            show_proute(temp_x,temp_y,g,first,false,true);
            break;
        case rook :
            show_rroute(temp_x,temp_y,g,false,true);
            break;
        case knight :
            show_nroute(temp_x,temp_y,g,false,true);
            break;
        case bishop :
            show_broute(temp_x,temp_y,g,false,true);
            break;
        case queen :
            show_qroute(temp_x,temp_y,g,false,true);
            break;
        case king :
            show_kroute(temp_x,temp_y,g,first,false,true);
            break;
        default:
            break;
        }
    }
}

void MainWindow::route_judge(bool real){
    vector < board_info > pos_record;
    const board_info temp_ = temp;
    board_info element = temp_;
    //record
    for(int x = 0 ; x < 8 ; ++ x)
        for(int y = 0 ; y < 8 ; ++ y)
            if(board[x][y].legal){
                pos_record.push_back(board[x][y]);
            }
    //if move,thinking
    board[element.xindex][element.yindex].id = none;
    board[element.xindex][element.yindex].group = -1;
    board[element.xindex][element.yindex].index = -1;
    reset_route(false);

    //test data
    pieces c;
    piece_id temp_legal_id;
    board_info temp_legal_info;
    int king_x = chess_pieces[element.group][12].x;
    int king_y = chess_pieces[element.group][12].y;
    for(unsigned long i = 0 ; i < pos_record.size() ; ++ i){
        temp_legal_info = board[pos_record[i].xindex][pos_record[i].yindex];
        temp_legal_id = temp_legal_info.id;
        if(element.id == king){
            king_x = pos_record[i].xindex;
            king_y = pos_record[i].yindex;
        }
        board[pos_record[i].xindex][pos_record[i].yindex].group = temp_.group;
        board[pos_record[i].xindex][pos_record[i].yindex].id = temp_.id;
        board[pos_record[i].xindex][pos_record[i].yindex].index = temp_.index;
        for(int chess = 0 ; chess < 16 ; ++ chess){
            c = chess_pieces[!element.group][chess];
            if(temp_legal_id != c.id && c.alive){
                switch(c.id) {
                case pawn :
                    show_proute(c.x,c.y,c.group,c.first,true,true);
                    break;
                case rook :
                    show_rroute(c.x,c.y,c.group,true,true);
                    break;
                case knight :
                    show_nroute(c.x,c.y,c.group,true,true);
                    break;
                case bishop :
                    show_broute(c.x,c.y,c.group,true,true);
                    break;
                case queen :
                    show_qroute(c.x,c.y,c.group,true,true);
                    break;
                case king :
                    show_kroute(c.x,c.y,c.group,c.first,true,true);
                    break;
                default:
                    break;
                }
            }
        }
        //close illegal pos
        if(board[king_x][king_y].legal)
            pos_record[i].legal = false;
        //clear temp teest
        reset_route(false);
        board[pos_record[i].xindex][pos_record[i].yindex] = temp_legal_info;
    }

    for(unsigned long i = 0 ; i < pos_record.size() ; ++ i){
        if(pos_record[i].legal){
            board[pos_record[i].xindex][pos_record[i].yindex].legal = true;
            if(real){
                board[pos_record[i].xindex][pos_record[i].yindex].color->setPixmap(b_color[1].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
                board[pos_record[i].xindex][pos_record[i].yindex].color->show();
            }
        }
    }
    //recover original
    if(real){
        board[element.xindex][element.yindex].color->setPixmap(b_color[0].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
        board[element.xindex][element.yindex].color->show();
    }
    board[element.xindex][element.yindex] = temp_;
}

void MainWindow::set_piece() {
    turn=pturn;
    pturn=!pturn;
    done=false;
    if(board[t_info.xindex][t_info.yindex].legal) {
        reset_route(true);

        //clear original pos info
        board[temp.xindex][temp.yindex].id=none;
        board[temp.xindex][temp.yindex].group=-1;
        board[temp.xindex][temp.yindex].index=-1;
        //pawn become queen
        if(temp.id==pawn && temp.yindex == 7-5*turn-1) {
            //set record
            game_record[record_index].key = pawn_queen;
            game_record[record_index].is_first = chess_pieces[turn][temp.index].first;
            game_record[record_index].second_xindex = -1;
            game_record[record_index].second_yindex = -1;
            game_record[record_index].second_index = -1;
            game_record[record_index].second_group = -1;
            //update info
            board[t_info.xindex][t_info.yindex].group=turn;
            board[t_info.xindex][t_info.yindex].id=queen;
            board[t_info.xindex][t_info.yindex].index=temp.index;
            animation(0,turn,temp,t_info);
            chess_pieces[turn][temp.index].id=queen;
            chess_pieces[turn][temp.index].special_skill=false;
            chess_pieces[turn][temp.index].x = t_info.xindex;
            chess_pieces[turn][temp.index].y = t_info.yindex;
            chess_pieces[turn][temp.index].img->setGeometry(board_xpos[t_info.xindex],board_ypos[t_info.yindex],block_width,block_width);
            chess_pieces[turn][temp.index].img->setPixmap(piece[turn][queen].scaled(block_width,block_width,Qt::KeepAspectRatio));
        }
        //king go into rook case
        else if(temp.id==king && chess_pieces[turn][temp.index].first && (temp.xindex-t_info.xindex==-2|| temp.xindex-t_info.xindex==2)) {
            if(temp.xindex-t_info.xindex==-2) {
                //set record
                game_record[record_index].key = king_rightrook;
                game_record[record_index].is_first = chess_pieces[turn][temp.index].first;
                game_record[record_index].second_xindex = 7;
                game_record[record_index].second_yindex = 7 - 7 * (!temp.group);
                game_record[record_index].second_index = 15;
                game_record[record_index].second_group = temp.group;
                //uupdate info
                board[t_info.xindex][t_info.yindex].group=turn;
                board[t_info.xindex][t_info.yindex].id=temp.id;
                board[t_info.xindex][t_info.yindex].index=temp.index;
                board[7][temp.yindex].group=-1;
                board[7][temp.yindex].id=none;
                board[7][temp.yindex].index=-1;
                board[5][temp.yindex].group=turn;
                board[5][temp.yindex].id=rook;
                board[5][temp.yindex].index=15;
                animation(1,turn,temp,t_info);
                chess_pieces[turn][15].x = t_info.xindex - 1;
                chess_pieces[turn][15].y = t_info.yindex;
                chess_pieces[turn][temp.index].x = t_info.xindex;
                chess_pieces[turn][temp.index].y = t_info.yindex;
                chess_pieces[turn][15].img->setGeometry(board_xpos[t_info.xindex-1],board_ypos[t_info.yindex],block_width,block_width);
                chess_pieces[turn][temp.index].img->setGeometry(board_xpos[t_info.xindex],board_ypos[t_info.yindex],block_width,block_width);
            }
            else {
                //set record
                game_record[record_index].key = king_leftrook;
                game_record[record_index].is_first = chess_pieces[turn][temp.index].first;
                game_record[record_index].second_xindex = 0;
                game_record[record_index].second_yindex = 7 - 7 * (!temp.group);
                game_record[record_index].second_index = 8;
                game_record[record_index].second_group = temp.group;
                //update info
                board[t_info.xindex][t_info.yindex].group=turn;
                board[t_info.xindex][t_info.yindex].id=temp.id;
                board[t_info.xindex][t_info.yindex].index=temp.index;
                board[0][temp.yindex].group=-1;
                board[0][temp.yindex].id=none;
                board[0][temp.yindex].index=-1;
                board[3][temp.yindex].group=turn;
                board[3][temp.yindex].id=rook;
                board[3][temp.yindex].index=8;
                animation(2,turn,temp,t_info);
                chess_pieces[turn][8].x = t_info.xindex + 1;
                chess_pieces[turn][8].y = t_info.yindex;
                chess_pieces[turn][temp.index].x = t_info.xindex;
                chess_pieces[turn][temp.index].y = t_info.yindex;
                chess_pieces[turn][8].img->setGeometry(board_xpos[t_info.xindex + 1],board_ypos[t_info.yindex],block_width,block_width);
                chess_pieces[turn][temp.index].img->setGeometry(board_xpos[t_info.xindex],board_ypos[t_info.yindex],block_width,block_width);
            }
        }
        //general case
        else {
            //set record
            game_record[record_index].key = nothing;
            game_record[record_index].is_first = chess_pieces[turn][temp.index].first;
            game_record[record_index].second_xindex = -1;
            game_record[record_index].second_yindex = -1;
            game_record[record_index].second_index = -1;
            game_record[record_index].second_group = -1;
            //update info
            board[t_info.xindex][t_info.yindex].group=turn;
            board[t_info.xindex][t_info.yindex].id=temp.id;
            board[t_info.xindex][t_info.yindex].index=temp.index;
            animation(0,turn,temp,t_info);
            chess_pieces[turn][temp.index].x = t_info.xindex;
            chess_pieces[turn][temp.index].y = t_info.yindex;
            chess_pieces[turn][temp.index].img->setGeometry(board_xpos[t_info.xindex],board_ypos[t_info.yindex],block_width,block_width);
        }
        //op piece dead
        if(t_info.id!=none){
            set_dead(t_info.group,t_info.index);
        }
        //eating pass-the-road pawn
        else if(temp.id == pawn && t_info.xindex - temp.xindex !=0 && t_info.group ==-1){
            set_dead(game_record[record_index - 1].from.group,game_record[record_index - 1].from.index);
            //set record
            game_record[record_index].key = pawn_pass;
            game_record[record_index].is_first = chess_pieces[!temp.group][game_record[record_index - 1].from.index].first;
            game_record[record_index].second_xindex = game_record[record_index - 1].to.xindex;
            game_record[record_index].second_yindex = game_record[record_index - 1].to.yindex;
            game_record[record_index].second_index = game_record[record_index - 1].from.index;
            game_record[record_index].second_group = game_record[record_index - 1].from.group;
        }
        //put sound
        put_sound->stop();
        put_sound->play();
        //close first
        chess_pieces[turn][temp.index].first=false;
        chess_pieces[turn][temp.index].img->update();
        game_judge();
    }
}

void MainWindow::game_judge(){
    //record temp turn
    if(record_index>=0 && record_index<1000){
        //record
        game_record[record_index].from=temp;
        game_record[record_index].to=t_info;
        game_record[record_index].from.yindex = temp.yindex ;
        ++record_index;
        //check if thread
        cout<<"555"<<endl;
        if(king_check()){
            if(!check_solved(pturn)){
                win_sound[temp.group]->stop();
                win_sound[temp.group]->play();
                QMessageBox::warning(this,"WARNING","-- GAMEOVER!!! --",QMessageBox::Ok);
            }
            else{
                check_sound[temp.group]->stop();
                check_sound[temp.group]->play();
            }
        }
        cout<<"move done"<<endl;
        debug();
        //updown();

    }
    else if(record_index >= 1000){
        QMessageBox::warning(this,"WARNING","YOU PLAY TOO LONG",QMessageBox::Ok);
    }
    else{
        QMessageBox::warning(this,"ERROR","WRONG PUSH",QMessageBox::Ok);
    }
    done=true;
}

bool MainWindow::king_check(){
    bool is_check = false;
    const bool test_g = temp.group;
    const int king_x = chess_pieces[!test_g][12].x;//king x pos
    const int king_y = chess_pieces[!test_g][12].y;//king y pos

    //check op weather my king will be checkmate
    pieces t;
    if(king_x >= 0 && king_x < 8 && king_y >=0 && king_y < 8){
        for(int chess = 0 ; chess < 16 ; ++ chess){
            t = chess_pieces[test_g][chess];
            if(t.alive){
                switch(board[t.x][t.y].id) {
                case pawn :
                    show_proute(t.x,t.y,t.group,t.first,true,false);
                    break;
                case rook :
                    show_rroute(t.x,t.y,t.group,true,false);
                    break;
                case knight :
                    show_nroute(t.x,t.y,t.group,true,false);
                    break;
                case bishop :
                    show_broute(t.x,t.y,t.group,true,false);
                    break;
                case queen :
                    show_qroute(t.x,t.y,t.group,true,false);
                    break;
                default:
                    break;
                }
            }
            if(board[king_x][king_y].legal){
                is_check = true;
                board[t.x][t.y].color->setPixmap(b_color[2].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
                board[t.x][t.y].color->show();
                board[king_x][king_y].color->setPixmap(b_color[2].scaled(block_width-10,block_width-10,Qt::KeepAspectRatio));
                board[king_x][king_y].color->show();
            }
            reset_route(false);
        }
    }
    return is_check;
}

bool MainWindow::check_solved(const bool opgroup){
    pieces c;
    const board_info t = temp;
    for(int chess = 0 ; chess < 16 ; ++ chess){
        c = chess_pieces[opgroup][chess];//assign my piece
        if(c.alive){
            temp = board[c.x][c.y];//modify temp
            switch(temp.id) {
            case pawn :
                show_proute(c.x,c.y,c.group,c.first,false,false);
                break;
            case rook :
                show_rroute(c.x,c.y,c.group,false,false);
                break;
            case knight :
                show_nroute(c.x,c.y,c.group,false,false);
                break;
            case bishop :
                show_broute(c.x,c.y,c.group,false,false);
                break;
            case queen :
                show_qroute(c.x,c.y,c.group,false,false);
                break;
            case king :
                show_kroute(c.x,c.y,c.group,c.first,false,false);
                break;
            default:
                break;
            }
            for(int x = 0 ; x < 8 ; ++ x)
                for(int y = 0 ; y < 8 ; ++ y)
                    if(board[x][y].legal){
                        temp = t;//reset temp
                        return true;
                    }
        }
    }
    //QMessageBox::warning(this,"WARNING","YOU PLAY TOO LONG",QMessageBox::Ok);
    temp = t;//reset temp
    return false;
}

void MainWindow::animation(const int key,const bool turn,const board_info temp,const board_info t_info){
    double x_,y_,x1_,y1_;
    int x_pos,y_pos,x1_pos,y1_pos,s_rate;

    //animation coefficient
    s_rate=static_cast<int>(sqrt(pow(t_info.xindex-temp.xindex,2)+pow(t_info.yindex-temp.yindex,2))*SLOWRATE);
    switch(key){
    case 0:
        x_=(board_xpos[t_info.xindex]-board_xpos[temp.xindex])/s_rate;
        y_=(board_ypos[t_info.yindex]-board_ypos[temp.yindex])/s_rate;
        for(int i=0; i<s_rate; ++i) {
            x_pos=static_cast<int>(board_xpos[temp.xindex]+x_*i);
            y_pos=static_cast<int>(board_ypos[temp.yindex]+y_*i);
            chess_pieces[turn][temp.index].img->setGeometry(x_pos,y_pos,block_width,block_width);
            chess_pieces[turn][temp.index].img->update();
            QCoreApplication::processEvents();
        }
        break;
    case 1:
        x_=(board_xpos[t_info.xindex]-board_xpos[temp.xindex])/s_rate;
        y_=(board_ypos[t_info.yindex]-board_ypos[temp.yindex])/s_rate;
        x1_=(board_xpos[t_info.xindex-1]-board_xpos[7])/s_rate;
        y1_=(board_ypos[t_info.yindex]-board_ypos[temp.yindex])/s_rate;
        for(int i=0; i<s_rate; ++i) {
            x_pos=static_cast<int>(board_xpos[temp.xindex]+x_*i);
            y_pos=static_cast<int>(board_ypos[temp.yindex]+y_*i);
            x1_pos=static_cast<int>(board_xpos[7]+x1_*i);
            y1_pos=static_cast<int>(board_ypos[temp.yindex]+y1_*i);
            chess_pieces[turn][temp.index].img->setGeometry(x_pos,y_pos,block_width,block_width);
            chess_pieces[turn][temp.index].img->update();
            chess_pieces[turn][15].img->setGeometry(x1_pos,y1_pos,block_width,block_width);
            chess_pieces[turn][15].img->update();
            QCoreApplication::processEvents();
        }
        break;
    case 2:
        x_=(board_xpos[t_info.xindex]-board_xpos[temp.xindex])/s_rate;
        y_=(board_ypos[t_info.yindex]-board_ypos[temp.yindex])/s_rate;
        x1_=(board_xpos[t_info.xindex+1]-board_xpos[0])/s_rate;
        y1_=(board_ypos[t_info.yindex]-board_ypos[temp.yindex])/s_rate;
        for(int i=0; i<s_rate; ++i) {
            x_pos=static_cast<int>(board_xpos[temp.xindex]+x_*i);
            y_pos=static_cast<int>(board_ypos[temp.yindex]+y_*i);
            x1_pos=static_cast<int>(board_xpos[0]+x1_*i);
            y1_pos=static_cast<int>(board_ypos[temp.yindex]+y1_*i);
            chess_pieces[turn][temp.index].img->setGeometry(x_pos,y_pos,block_width,block_width);
            chess_pieces[turn][temp.index].img->update();
            chess_pieces[turn][8].img->setGeometry(x1_pos,y1_pos,block_width,block_width);
            chess_pieces[turn][8].img->update();
            QCoreApplication::processEvents();
        }
        break;
    }
}

void MainWindow::undo_set(){

    int tx1,ty1,tx2,ty2;
    short second_i;
    bool second_g;
    pieces *t1,*t2;
    if(record_index == 0){
        QMessageBox::warning(nullptr,tr("ERROR"),tr("Can't undo now!!!"),QMessageBox::Ok);
    }else{
        for(int set = 0 ; set < 1 ; ++ set){
            -- record_index;
            pturn = !pturn;
            //dead
           if(game_record[record_index].to.id != none ){
                tx1 = game_record[record_index].to.xindex;
                ty1 = game_record[record_index].to.yindex;
                t1 = &chess_pieces[game_record[record_index].to.group][game_record[record_index].to.index];
                t1->img->setGeometry(board_xpos[tx1],board_ypos[ty1],block_width,block_width);
                t1->img->setPixmap(piece[t1->group][t1->id].scaled(block_width,block_width,Qt::KeepAspectRatio));
                t1->x = tx1;
                t1->y = ty1;
                t1->img->update();
                t1->alive = true;
                board[tx1][ty1].id = t1->id;
                board[tx1][ty1].group = t1->group;
                board[tx1][ty1].index = game_record[record_index].to.index;

                //QMessageBox::information(nullptr,tr("ERROR"),tr("!!!"),QMessageBox::Ok);
            }

            switch(game_record[record_index].key){
            case nothing:
            case pawn_pass:
                tx1 = game_record[record_index].from.xindex;
                ty1 = game_record[record_index].from.yindex;
                t1 = &chess_pieces[game_record[record_index].from.group][game_record[record_index].from.index];
                t1->img->setGeometry(board_xpos[tx1],board_ypos[ty1],block_width,block_width);
                t1->img->setPixmap(piece[t1->group][t1->id].scaled(block_width,block_width,Qt::KeepAspectRatio));
                t1->x = tx1;
                t1->y = ty1;
                t1->img->update();
                if(game_record[record_index].is_first == true)
                    t1->first = true;
                board[tx1][ty1].id = t1->id;
                board[tx1][ty1].group = t1->group;
                board[tx1][ty1].index = game_record[record_index].from.index;
                if(game_record[record_index].to.id == none ){
                    tx2 = game_record[record_index].to.xindex;
                    ty2 = game_record[record_index].to.yindex;
                    board[tx2][ty2].id = none;
                    board[tx2][ty2].group = -1;
                    board[tx2][ty2].index = -1;
                }
                break;
            case pawn_queen:
                tx1 = game_record[record_index].from.xindex;
                ty1 = game_record[record_index].from.yindex;
                t1 = &chess_pieces[game_record[record_index].from.group][game_record[record_index].from.index];
                t1->id = pawn;
                t1->img->setGeometry(board_xpos[tx1],board_ypos[ty1],block_width,block_width);
                t1->x = tx1;
                t1->y = ty1;
                t1->img->update();
                board[tx1][ty1].id = t1->id;
                board[tx1][ty1].group = t1->group;
                board[tx1][ty1].index = game_record[record_index].from.index;
                if(game_record[record_index].to.id == none ){
                    tx2 = game_record[record_index].to.xindex;
                    ty2 = game_record[record_index].to.yindex;
                    board[tx2][ty2].id = none;
                    board[tx2][ty2].group = -1;
                    board[tx2][ty2].index = -1;
                }
                break;
            case king_leftrook:
                tx1 = game_record[record_index].from.xindex;
                ty1 = game_record[record_index].from.yindex;
                tx2 = game_record[record_index].second_xindex;
                ty2 = game_record[record_index].second_yindex;
                second_g = game_record[record_index].second_group;
                second_i = game_record[record_index].second_index;
                t1 = &chess_pieces[game_record[record_index].from.group][game_record[record_index].from.index];
                t2 = &chess_pieces[second_g][second_i];
                t1->img->setGeometry(board_xpos[tx1],board_ypos[ty1],block_width,block_width);
                t2->img->setGeometry(board_xpos[tx2],board_ypos[ty2],block_width,block_width);
                t1->x = tx1;
                t2->x = tx2;
                t1->y = ty1;
                t2->y = ty2;
                t1->img->update();
                t2->img->update();
                board[tx1][ty1].id = t1->id;
                board[tx1][ty1].group = t1->group;
                board[tx1][ty1].index = game_record[record_index].from.index;
                board[tx2][ty2].id = t1->id;
                board[tx2][ty2].group = t1->group;
                board[tx2][ty2].index = game_record[record_index].from.index;
                board[3][ty1].id = none;
                board[3][ty1].group = -1;
                board[3][ty1].index = -1;
                board[2][ty1].id = none;
                board[2][ty1].group = -1;
                board[2][ty1].index = -1;
                break;
            case king_rightrook:
                tx1 = game_record[record_index].from.xindex;
                ty1 = game_record[record_index].from.yindex;
                tx2 = game_record[record_index].second_xindex;
                ty2 = game_record[record_index].second_yindex;
                second_g = game_record[record_index].second_group;
                second_i = game_record[record_index].second_index;
                t1 = &chess_pieces[game_record[record_index].from.group][game_record[record_index].from.index];
                t2 = &chess_pieces[second_g][second_i];
                t1->img->setGeometry(board_xpos[tx1],board_ypos[ty1],block_width,block_width);
                t2->img->setGeometry(board_xpos[tx2],board_ypos[ty2],block_width,block_width);
                t1->x = tx1;
                t2->x = tx2;
                t1->y = ty1;
                t2->y = ty2;
                t1->img->update();
                t2->img->update();
                board[tx1][ty1].id = t1->id;
                board[tx1][ty1].group = t1->group;
                board[tx1][ty1].index = game_record[record_index].from.index;
                board[tx2][ty2].id = t1->id;
                board[tx2][ty2].group = t1->group;
                board[tx2][ty2].index = game_record[record_index].from.index;
                board[5][ty1].id = none;
                board[5][ty1].group = -1;
                board[5][ty1].index = -1;
                board[6][ty1].id = none;
                board[6][ty1].group = -1;
                board[6][ty1].index = -1;
                break;
            }
        }
       // cout<< t1->group << " : " << t1->id << " " << game_record[record_index].from.index <<endl;
        reset_route(true);
        cout<<"- undo - "<<endl;
        debug();
    }
}

void MainWindow::updown() {
    board_info temp_board[8][8];
    pieces temp_pieces[2][16];
    //chess updown
    /*board_info t;
    for(int x = 0 ; x < 8 ; ++ x)
        for(int y = 0 ; y < 8 ; ++ y){
            board[x][y].color->setGeometry(board_xpos[x]+5,board_ypos[7-y]+5,block_width,block_width);
            if(board[x][y].id != none){
                t = board[x][y];
                chess_pieces[t.group][t.index].img->close();
                chess_pieces[t.group][t.index].img->setGeometry(board_xpos[x],board_ypos[7-y],block_width,block_width);
                chess_pieces[t.group][t.index].img->show();
            }
        }
    cout<<"updown"<<endl;
    up_down = ! up_down;
    debug();*/
    for(int x = 0 ; x < 8 ; ++ x)
        for(int y = 0 ; y < 8 ; ++ y){
            board[x][y].id = temp_board[x][y].id;
            board[x][y].index = temp_board[x][y].index;
            board[x][y].group = temp_board[x][y].group;
        }
    board_info t;
    for(int x = 0 ; x < 8 ; ++ x)
        for(int y = 0 ; y < 8 ; ++ y){
            if(board[x][y].id != none){
                t = board[x][y];
                chess_pieces[t.group][t.index].img->close();
                chess_pieces[t.group][t.index].x = x;
                chess_pieces[t.group][t.index].y = y;
                chess_pieces[t.group][t.index].img->setGeometry(board_xpos[x],board_ypos[y],block_width,block_width);
                chess_pieces[t.group][t.index].img->show();
                //QCoreApplication::processEvents();
            }
        }
    cout<<"updown"<<endl;
    up_down = ! up_down;
    debug();
}

void MainWindow::set_dead(bool group,short index) {
    piece_id dead_id = chess_pieces[group][index].id;
    //dead sound
    if(start){
        dead->stop();
        dead->play();
    }
    chess_pieces[group][index].alive=false;
    chess_pieces[group][index].img->setGeometry
    (dead_xpos[dead_count[group]],dead_ypos[group],dead_width,dead_width);
    chess_pieces[group][index].x = -1;
    chess_pieces[group][index].y = -1;
    chess_pieces[group][index].img->setPixmap(piece[group][dead_id].scaled(dead_width,dead_width,Qt::KeepAspectRatio));
    chess_pieces[group][index].img->update();
    ++dead_count[group];
    cout<<"dead: group "<<group<<" count "<<dead_count[group]<<endl;
}

void MainWindow::show_proute(int temp_x,int temp_y,bool g,bool first,bool think,bool real) {
    //black
    if(g==0) {
        //front one
        if( temp_y+1 < 8 && board[temp_x][temp_y+1].group == -1 ) {
            if(!think){
                board[temp_x][temp_y+1].legal=true;
            }
        }
        //kill left
        if( temp_x-1 >= 0 && temp_y + 1 < 8 && board[temp_x-1][temp_y+1].group == 1) {
            board[temp_x-1][temp_y+1].legal=true;
        }
        //kill right
        if( temp_x+1 < 8 && temp_y+1 < 8 && board[temp_x+1][temp_y+1].group == 1) {
            board[temp_x+1][temp_y+1].legal=true;
        }
        //front two
        if( board[temp_x][temp_y+2].group==-1 && first && board[temp_x][temp_y+1].group==-1) {
            if(!think){
                board[temp_x][temp_y+2].legal=true;
            }
        }
        //pawn pass left
        if(record_index-1 >= 0 && game_record[record_index-1].from.id == pawn &&
                temp_x - game_record[record_index-1].to.xindex == 1 &&
                temp_y == game_record[record_index-1].to.yindex){
            if(game_record[record_index-1].to.yindex - game_record[record_index-1].from.yindex == -2){
                board[temp_x-1][temp_y+1].legal=true;
            }
        }
        //pawn pass right
        if(record_index-1 >= 0 && game_record[record_index-1].from.id == pawn &&
                temp_x - game_record[record_index-1].to.xindex == -1 &&
                temp_y == game_record[record_index-1].to.yindex){
            if(game_record[record_index-1].to.yindex - game_record[record_index-1].from.yindex == -2){
                board[temp_x+1][temp_y+1].legal=true;
            }
        }
        //turn to queen
        if(temp_y==6) {
            //front
            if(!think && board[temp_x][temp_y+1].group == -1) {
                board[temp_x][temp_y+1].legal=true;
            }
            //left
            if(board[temp_x-1][temp_y+1].group == 1) {
                board[temp_x-1][temp_y+1].legal=true;
            }
            //right
            if(board[temp_x+1][temp_y+1].group == 1) {
                board[temp_x+1][temp_y+1].legal=true;
            }
        }
    }
    //white
    else if(g) {
        //front one
        if( temp_y-1 >= 0 && board[temp_x][temp_y-1].group == -1 ) {
            if(!think){
                board[temp_x][temp_y-1].legal=true;
            }
        }
        //kill left
        if( temp_x-1 >= 0 && temp_y-1 >= 0 && board[temp_x-1][temp_y-1].group == !g ) {
            board[temp_x-1][temp_y-1].legal=true;
        }
        //kill right
        if( temp_x+1 < 8 && temp_y-1 >= 0 && board[temp_x+1][temp_y-1].group == !g) {
            board[temp_x+1][temp_y-1].legal=true;
        }
        //front two
        if( board[temp_x][temp_y-2].group==-1 && first && board[temp_x][temp_y-1].group==-1) {
            if(!think){
                board[temp_x][temp_y-2].legal=true;
            }
        }
        //pawn pass left
        if(record_index-1 >= 0 && game_record[record_index-1].from.id == pawn &&
                temp_x - game_record[record_index-1].to.xindex == 1 &&
                temp_y == game_record[record_index-1].to.yindex){
            if(game_record[record_index-1].to.yindex - game_record[record_index-1].from.yindex == 2){
                board[temp_x-1][temp_y-1].legal=true;
                board[temp_x-1][temp_y-1].color->show();
            }
        }
        //pawn pass right
        if(record_index-1 >= 0 && game_record[record_index-1].from.id == pawn &&
                temp_x - game_record[record_index-1].to.xindex == -1 &&
                temp_y == game_record[record_index-1].to.yindex){
            if(game_record[record_index-1].to.yindex - game_record[record_index-1].from.yindex == 2){
                board[temp_x+1][temp_y-1].legal=true;
                board[temp_x+1][temp_y-1].color->show();
            }
        }
        //turn to queen
        if(temp_y==1) {
            //front
            if(!think && board[temp_x][temp_y-1].group == -1) {
                board[temp_x][temp_y-1].legal=true;
            }
            //left
            if(board[temp_x-1][temp_y-1].group == !g) {
                board[temp_x-1][temp_y-1].legal=true;
            }
            //right
            if(board[temp_x+1][temp_y-1].group == !g) {
                board[temp_x+1][temp_y-1].legal=true;
            }
        }
    }

    if(!think){
        route_judge(real);
    }
    //debug();
}

void MainWindow::show_rroute(int temp_x,int temp_y,bool g,bool think,bool real) {
    //right
    for(int i=1; temp_x+i<8 && board[temp_x+i][temp_y].group!=g ; ++i) {
        board[temp_x+i][temp_y].legal=true;
        if(!think && board[temp_x+i][temp_y].group==!g) break;
        else if(think && board[temp_x+i][temp_y].group==!g && board[temp_x+i][temp_y].id != king) break;
    }
    //left
    for(int i=1; temp_x-i>=0 && board[temp_x-i][temp_y].group!=g ; ++i) {
        board[temp_x-i][temp_y].legal=true;
        if(!think && board[temp_x-i][temp_y].group==!g) break;
        else if(think && board[temp_x-i][temp_y].group==!g && board[temp_x-i][temp_y].id != king) break;
    }
    //up
    for(int j=1; temp_y-j>=0 && board[temp_x][temp_y-j].group!=g ; ++j) {
        board[temp_x][temp_y-j].legal=true;
        if(!think && board[temp_x][temp_y-j].group==!g) break;
        else if(think && board[temp_x][temp_y-j].group==!g && board[temp_x][temp_y-j].id != king) break;
    }
    //down
    for(int j=1; temp_y+j<8 && board[temp_x][temp_y+j].group!=g ; ++j) {
        board[temp_x][temp_y+j].legal=true;
        if(!think && board[temp_x][temp_y+j].group==!g) break;
        else if(think && board[temp_x][temp_y+j].group==!g && board[temp_x][temp_y+j].id != king) break;
    }
    if(!think)
        route_judge(real);
}
void MainWindow::show_nroute(int temp_x,int temp_y,bool g,bool think,bool real) {
    if(temp_x+1<8 && temp_y+2<8 && board[temp_x+1][temp_y+2].group!=g) {
        board[temp_x+1][temp_y+2].legal=true;
    }
    if(temp_x+2<8 && temp_y+1<8 && board[temp_x+2][temp_y+1].group!=g) {
        board[temp_x+2][temp_y+1].legal=true;
    }
    if(temp_x+2<8 && temp_y-1>=0 && board[temp_x+2][temp_y-1].group!=g) {
        board[temp_x+2][temp_y-1].legal=true;
    }
    if(temp_x+1<8 && temp_y-2>=0 && board[temp_x+1][temp_y-2].group!=g) {
        board[temp_x+1][temp_y-2].legal=true;
    }
    if(temp_x-1>=0 && temp_y-2>=0 && board[temp_x-1][temp_y-2].group!=g) {
        board[temp_x-1][temp_y-2].legal=true;
    }
    if(temp_x-2>=0 && temp_y-1>=0 && board[temp_x-2][temp_y-1].group!=g) {
        board[temp_x-2][temp_y-1].legal=true;
    }
    if(temp_x-2>=0 && temp_y+1<8 && board[temp_x-2][temp_y+1].group!=g) {
        board[temp_x-2][temp_y+1].legal=true;
    }
    if(temp_x-1>=0 && temp_y+2<8 && board[temp_x-1][temp_y+2].group!=g) {
        board[temp_x-1][temp_y+2].legal=true;
    }
    if(!think)
        route_judge(real);
}
void MainWindow::show_broute(int temp_x,int temp_y,bool g,bool think,bool real) {
    //down-right
    for(int i=1; temp_x+i<8 && temp_y+i<8 && board[temp_x+i][temp_y+i].group!=g ; ++i) {
        board[temp_x+i][temp_y+i].legal=true;
        if(!think && board[temp_x+i][temp_y+i].group==!g) break;
        else if(think && board[temp_x+i][temp_y+i].group==!g && board[temp_x+i][temp_y+i].id != king) break;
    }
    //down-left
    for(int i=1; temp_x-i>=0 && temp_y+i<8 && board[temp_x-i][temp_y+i].group!=g ; ++i) {
        board[temp_x-i][temp_y+i].legal=true;
        if(!think && board[temp_x-i][temp_y+i].group==!g) break;
        else if(think && board[temp_x-i][temp_y+i].group==!g && board[temp_x-i][temp_y+i].id != king) break;
    }
    //up-left
    for(int j=1; temp_x-j>=0 && temp_y-j>=0 && board[temp_x-j][temp_y-j].group!=g ; ++j) {
        board[temp_x-j][temp_y-j].legal=true;
        if(!think && board[temp_x-j][temp_y-j].group==!g) break;
        else if(think && board[temp_x-j][temp_y-j].group==!g && board[temp_x-j][temp_y-j].id != king) break;
    }
    //up-right
    for(int j=1; temp_x+j<8 && temp_y-j>=0 && board[temp_x+j][temp_y-j].group!=g ; ++j) {
        board[temp_x+j][temp_y-j].legal=true;
        if(!think && board[temp_x+j][temp_y-j].group==!g) break;
        else if(think && board[temp_x+j][temp_y-j].group==!g && board[temp_x+j][temp_y-j].id != king) break;
    }
    if(!think)
        route_judge(real);
}
void MainWindow::show_qroute(int temp_x,int temp_y,bool g,bool think,bool real) {
    //right
    for(int i=1; temp_x+i<8 && board[temp_x+i][temp_y].group!=g  ; ++i) {
        board[temp_x+i][temp_y].legal=true;
        if(!think && board[temp_x+i][temp_y].group == !g) break;
        else if(think && board[temp_x+i][temp_y].group == !g && board[temp_x+i][temp_y].id != king) break;
    }
    //left
    for(int i=1; temp_x-i>=0 && board[temp_x-i][temp_y].group!=g ; ++i) {
        board[temp_x-i][temp_y].legal=true;
        if(!think && board[temp_x-i][temp_y].group==!g) break;
        else if(think && board[temp_x-i][temp_y].group==!g && board[temp_x-i][temp_y].id != king) break;
    }
    //up
    for(int j=1; temp_y-j>=0 && board[temp_x][temp_y-j].group!=g ; ++j) {
        board[temp_x][temp_y-j].legal=true;
        if(!think && board[temp_x][temp_y-j].group==!g) break;
        else if(think && board[temp_x][temp_y-j].group==!g && board[temp_x][temp_y-j].id != king) break;
    }
    //down
    for(int j=1; temp_y+j<8 && board[temp_x][temp_y+j].group!=g ; ++j) {
        board[temp_x][temp_y+j].legal=true;
        if(!think && board[temp_x][temp_y+j].group==!g) break;
        else if(think && board[temp_x][temp_y+j].group==!g && board[temp_x][temp_y+j].id != king) break;
    }
    //down-right
    for(int i=1; temp_x+i<8 && temp_y+i<8 && board[temp_x+i][temp_y+i].group!=g ; ++i) {
        board[temp_x+i][temp_y+i].legal=true;
        if(!think && board[temp_x+i][temp_y+i].group==!g) break;
        else if(think && board[temp_x+i][temp_y+i].group==!g && board[temp_x+i][temp_y+i].id != king) break;
    }
    //down-left
    for(int i=1; temp_x-i>=0 && temp_y+i<8 && board[temp_x-i][temp_y+i].group!=g ; ++i) {
        board[temp_x-i][temp_y+i].legal=true;
        if(!think && board[temp_x-i][temp_y+i].group==!g) break;
        else if(think && board[temp_x-i][temp_y+i].group==!g && board[temp_x-i][temp_y+i].id != king) break;
    }
    //up-left
    for(int j=1; temp_x-j>=0 && temp_y-j>=0 && board[temp_x-j][temp_y-j].group!=g ; ++j) {
        board[temp_x-j][temp_y-j].legal=true;
        if(!think && board[temp_x-j][temp_y-j].group==!g) break;
        else if(think && board[temp_x-j][temp_y-j].group==!g && board[temp_x-j][temp_y-j].id != king) break;
    }
    //up-right
    for(int j=1; temp_x+j<8 && temp_y-j>=0 && board[temp_x+j][temp_y-j].group!=g ; ++j) {
        board[temp_x+j][temp_y-j].legal=true;
        if(!think && board[temp_x+j][temp_y-j].group==!g) break;
        else if(think && board[temp_x+j][temp_y-j].group==!g && board[temp_x+j][temp_y-j].id != king) break;
    }
    if(!think)
        route_judge(real);
}
void MainWindow::show_kroute(int temp_x,int temp_y,bool g,bool first,bool think,bool real) {

    if(temp_x+1<8 && board[temp_x+1][temp_y].group != g) {
        board[temp_x+1][temp_y].legal=true;
    }
    if(temp_x+1<8 && temp_y+1<8 && board[temp_x+1][temp_y+1].group != g) {
        board[temp_x+1][temp_y+1].legal=true;
    }
    if(temp_y+1<8 && board[temp_x][temp_y+1].group != g) {
        board[temp_x][temp_y+1].legal=true;
    }
    if(temp_x-1>=0 && temp_y+1<8 && board[temp_x-1][temp_y+1].group != g) {
        board[temp_x-1][temp_y+1].legal=true;
    }
    if(temp_x-1>=0 && board[temp_x-1][temp_y].group != g) {
        board[temp_x-1][temp_y].legal=true;
    }
    if(temp_x-1>=0 && temp_y-1>=0 && board[temp_x-1][temp_y-1].group != g) {
        board[temp_x-1][temp_y-1].legal=true;
    }
    if(temp_y-1>=0 && board[temp_x][temp_y-1].group != g) {
        board[temp_x][temp_y-1].legal=true;
    }
    if(temp_x+1<8 && temp_y-1>=0 &&board[temp_x+1][temp_y-1].group != g) {
        board[temp_x+1][temp_y-1].legal=true;
    }
    if(first && chess_pieces[g][8].first && chess_pieces[g][8].alive &&
            board[temp_x-1][temp_y].group==-1 &&
            board[temp_x-2][temp_y].group==-1 &&
            board[temp_x-3][temp_y].group==-1
      ) {
        board[temp_x-2][temp_y].legal=true;
    }
    if(first && chess_pieces[g][15].first && chess_pieces[g][15].alive &&
            board[temp_x+1][temp_y].group==-1 &&
            board[temp_x+2][temp_y].group==-1) {
        board[temp_x+2][temp_y].legal=true;
    }
    if(!think)
        route_judge(real);
}

void MainWindow::debug() {
    cout<<"------------------------"<<endl;
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            if(board[j][i].group==-1)
                cout<<".";
            else if(board[j][i].group==0)
                cout<<"b";
            else if(board[j][i].group==1)
                cout<<"w";
            cout<<board[j][i].id;
            if(board[j][i].group!=-1) {
                if(chess_pieces[board[j][i].group][board[j][i].index].first==true)
                    cout<<"t ";
                else
                    cout<<"f ";
            } else {
                cout<<". ";
            }
        }
        cout<<endl<<endl;
    }
    cout<<"------------------------"<<endl;
}

MainWindow::~MainWindow() {
    delete ui;
}
