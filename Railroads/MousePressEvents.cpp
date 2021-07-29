#include <dmainscreen.h>

void DMainScreen::mousePressEvent(QMouseEvent *event)
{

    if (READY)
        {

            switch (CurrentTool)
                {
                case TOOL_CHANGE_TERRAIN:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                        }
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                        break;
                    }


                case TOOL_LANDSCAPE_UP:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            increaseHeight(cursor_x,cursor_y+1);
                                            increaseHeight(cursor_x+1,cursor_y+1);
                                            increaseHeight(cursor_x,cursor_y);
                                            increaseHeight(cursor_x+1,cursor_y);
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }

                                    if (LastHoverGroup==HOVER_GROUP_CORNER)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            int ccx = GetCornerXFromID(LastHoverID);
                                            int ccy = GetCornerYFromID(LastHoverID);
                                            int typ = GetCornerTypeFromID(LastHoverID);

                                            switch (typ)
                                                {
                                                case CORNER_DL:
                                                    {
                                                        increaseHeight(ccx,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_DR:
                                                    {
                                                        increaseHeight(ccx+1,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_UL:
                                                    {
                                                        increaseHeight(ccx,ccy);
                                                        break;
                                                    }

                                                case CORNER_UR:
                                                    {
                                                        increaseHeight(ccx+1,ccy);
                                                        break;
                                                    }
                                                default: break;
                                                }
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }



                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                        break;
                    }

                case TOOL_LANDSCAPE_DOWN:
                    {

                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    break;
                                }

                            case Qt::LeftButton:
                                {

                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            decreaseHeight(cursor_x,cursor_y+1);
                                            decreaseHeight(cursor_x+1,cursor_y+1);
                                            decreaseHeight(cursor_x,cursor_y);
                                            decreaseHeight(cursor_x+1,cursor_y);
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }

                                    if (LastHoverGroup==HOVER_GROUP_CORNER)
                                        {
                                            //cells[cursor_x][cursor_y].type = (cells[cursor_x][cursor_y].type+1)%16;
                                            int ccx = GetCornerXFromID(LastHoverID);
                                            int ccy = GetCornerYFromID(LastHoverID);
                                            int typ = GetCornerTypeFromID(LastHoverID);

                                            switch (typ)
                                                {
                                                case CORNER_DL:
                                                    {
                                                        decreaseHeight(ccx,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_DR:
                                                    {
                                                        decreaseHeight(ccx+1,ccy+1);
                                                        break;
                                                    }

                                                case CORNER_UL:
                                                    {
                                                        decreaseHeight(ccx,ccy);
                                                        break;
                                                    }

                                                case CORNER_UR:
                                                    {
                                                        decreaseHeight(ccx+1,ccy);
                                                        break;
                                                    }
                                                default: break;
                                                }
                                            RENDER_BASIC_CALCULATE_NORMALS();
                                        }

                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }

                        break;
                    }

                case TOOL_TOGGLE_WATER:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    if (LastHoverGroup==HOVER_GROUP_TERRAIN)
                                        {
                                            if (cells[cursor_x][cursor_y].type==TERRAIN_TYPES_WATER)
                                                {
                                                    cells[cursor_x][cursor_y].type=TERRAIN_TYPES_DIRT;
                                                }
                                            else
                                                {
                                                    cells[cursor_x][cursor_y].type=TERRAIN_TYPES_WATER;
                                                    map[cursor_x][cursor_y] = -1;
                                                    map[cursor_x][cursor_y+1] = -1;
                                                    map[cursor_x+1][cursor_y] = -1;
                                                    map[cursor_x+1][cursor_y+1] = -1;
                                                }
                                        }
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }

                    }

                case TOOL_RAILROAD_PLACE_START:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    // check if we pressed the proper starting node
                                    // TODO: just check for node...

                                    bool correct = (LastHoverGroup==HOVER_GROUP_CORNER)||(LastHoverGroup==HOVER_GROUP_HOR_SIDE)||(LastHoverGroup==HOVER_GROUP_VER_SIDE);

                                    if (correct)
                                        {
                                         //   if (LastHoverGroup==HOVER_GROUP_HOR_SIDE)
                                               // correct = (HorizontalSideNodes[GetHorSideNode(LastHoverID).x()][GetHorSideNode(LastHoverID).y()].d==nullptr) || (HorizontalSideNodes[GetHorSideNode(LastHoverID).x()][GetHorSideNode(LastHoverID).y()].u==nullptr);

                                           // if (LastHoverGroup==HOVER_GROUP_VER_SIDE)
                                              //  correct = (VerticalSideNodes[GetVerSideNode(LastHoverID).x()][GetVerSideNode(LastHoverID).y()].l==nullptr) || (VerticalSideNodes[GetVerSideNode(LastHoverID).x()][GetVerSideNode(LastHoverID).y()].r==nullptr);

                                            if (LastHoverGroup==HOVER_GROUP_CORNER)
                                                {
                                                   // correct = ((CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].ul!=nullptr) && (CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].dr!=nullptr)) ||
                                                    //        ((CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].ur!=nullptr) && (CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].dl!=nullptr));
                                                    //correct =!correct;
                                                }
                                        }


                                    magnets.clear();
                                    if (correct)
                                        {
                                            HoverMagnet = nullptr;

                                            CurrentTool = TOOL_RAILROAD_PLACE_END;

                                            if (LastHoverGroup == HOVER_GROUP_CORNER)
                                                {
                                                    // RailStart = DNetworkNode(GetCornerNode(LastHoverID).x(),GetCornerNode(LastHoverID).y(),Orientations::Node);
                                                    RailStart.i=GetCornerNode(LastHoverID).x();
                                                    RailStart.j=GetCornerNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::corner;
                                                }

                                            if (LastHoverGroup == HOVER_GROUP_HOR_SIDE)
                                                {
                                                    // RailStart = DNetworkNode(GetCornerNode(LastHoverID).x(),GetCornerNode(LastHoverID).y(),Orientations::Node);
                                                    RailStart.i=GetHorSideNode(LastHoverID).x();
                                                    RailStart.j=GetHorSideNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::horiz;
                                                }

                                            if (LastHoverGroup == HOVER_GROUP_VER_SIDE)
                                                {
                                                    RailStart.i=GetVerSideNode(LastHoverID).x();
                                                    RailStart.j=GetVerSideNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::vert;
                                                }



                                            PREPARE_MAGNETS_END();

                                        }
                                    else
                                        {
                                            //error...
                                        }

                                    break;
                                }

                            default: QWidget::mousePressEvent(event);
                            }

                        break;
                    }


                case TOOL_ROAD_PLACE_START:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    // check if we pressed the proper starting node
                                    // TODO: just check for node...

                                    bool correct = (LastHoverGroup==HOVER_GROUP_CORNER)||(LastHoverGroup==HOVER_GROUP_HOR_SIDE)||(LastHoverGroup==HOVER_GROUP_VER_SIDE);

                                    if (correct)
                                        {
                                         //   if (LastHoverGroup==HOVER_GROUP_HOR_SIDE)
                                               // correct = (HorizontalSideNodes[GetHorSideNode(LastHoverID).x()][GetHorSideNode(LastHoverID).y()].d==nullptr) || (HorizontalSideNodes[GetHorSideNode(LastHoverID).x()][GetHorSideNode(LastHoverID).y()].u==nullptr);

                                           // if (LastHoverGroup==HOVER_GROUP_VER_SIDE)
                                              //  correct = (VerticalSideNodes[GetVerSideNode(LastHoverID).x()][GetVerSideNode(LastHoverID).y()].l==nullptr) || (VerticalSideNodes[GetVerSideNode(LastHoverID).x()][GetVerSideNode(LastHoverID).y()].r==nullptr);

                                            if (LastHoverGroup==HOVER_GROUP_CORNER)
                                                {
                                                   // correct = ((CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].ul!=nullptr) && (CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].dr!=nullptr)) ||
                                                    //        ((CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].ur!=nullptr) && (CornerNodes[GetCornerNode(LastHoverID).x()][GetCornerNode(LastHoverID).y()].dl!=nullptr));
                                                    //correct =!correct;
                                                }
                                        }


                                    magnets.clear();
                                    if (correct)
                                        {
                                            HoverMagnet = nullptr;

                                            CurrentTool = TOOL_ROAD_PLACE_END;

                                            if (LastHoverGroup == HOVER_GROUP_CORNER)
                                                {
                                                    // RailStart = DNetworkNode(GetCornerNode(LastHoverID).x(),GetCornerNode(LastHoverID).y(),Orientations::Node);
                                                    RailStart.i=GetCornerNode(LastHoverID).x();
                                                    RailStart.j=GetCornerNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::corner;
                                                }

                                            if (LastHoverGroup == HOVER_GROUP_HOR_SIDE)
                                                {
                                                    // RailStart = DNetworkNode(GetCornerNode(LastHoverID).x(),GetCornerNode(LastHoverID).y(),Orientations::Node);
                                                    RailStart.i=GetHorSideNode(LastHoverID).x();
                                                    RailStart.j=GetHorSideNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::horiz;
                                                }

                                            if (LastHoverGroup == HOVER_GROUP_VER_SIDE)
                                                {
                                                    RailStart.i=GetVerSideNode(LastHoverID).x();
                                                    RailStart.j=GetVerSideNode(LastHoverID).y();
                                                    RailStart.type = NetworkNodeTypes::vert;
                                                }



                                            PREPARE_ROAD_MAGNETS_END();

                                        }
                                    else
                                        {
                                            //error...
                                        }

                                    break;
                                }

                            default: QWidget::mousePressEvent(event);
                            }

                        break;
                    }



                case TOOL_BULLDOSE:
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {

                                    if (LastHoverGroup == HOVER_GROUP_TERRAIN)
                                        {
                                            bulldose_rail(obstructions[cursor_x][cursor_y].u);
                                            bulldose_rail(obstructions[cursor_x][cursor_y].l);
                                            bulldose_rail(obstructions[cursor_x][cursor_y].d);
                                            bulldose_rail(obstructions[cursor_x][cursor_y].r);
                                           }

                                    // check if we pressed the something like UI element or active entity like train...
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                        break;
                    }



                default:// also TOOL_NONE
                    {
                        switch (event->button())
                            {
                            case Qt::RightButton:
                                {
                                    moving = true;
                                    movingx = event->x();
                                    movingy = event->y();
                                    break;
                                }

                            case Qt::LeftButton:
                                {
                                    // check if we pressed the something like UI element or active entity like train...
                                    break;
                                }
                            default: QWidget::mousePressEvent(event);
                            }
                    }

                }
        }
}
