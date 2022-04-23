#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>

#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSTLReader.h>
#include <vtkShrinkFilter.h>
#include <vtkPlane.h>
#include <vtkClipDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkDataSet.h>
#include<vtkOutlineFilter.h>

#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include <QColorDialog>

#include <stdio.h>
#include <string.h>

#include "filter.h"
#include <vtkDelaunay3D.h>
#include <vtkAppendFilter.h>
#include <vtkConnectivityFilter.h>

#include <vtkCutter.h>
#include <vtkElevationFilter.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>

#include <vector>
#include "form.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );

    // Now need to create a VTK render window and link it to the QtVTK widget
    ui->qvtkWidget_Tab1->SetRenderWindow( renderWindow );// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

    // Create a renderer, and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    ui->qvtkWidget_Tab1->GetRenderWindow()->AddRenderer( renderer );

    ui->qvtkWidget_Tab2->SetRenderWindow( renderWindow_Tab2 );
    renderer_Tab2 = vtkSmartPointer<vtkRenderer>::New();
    ui->qvtkWidget_Tab2->GetRenderWindow()->AddRenderer( renderer_Tab2 );

    // Set background to black
    renderer->SetBackground( colors->GetColor3d("black").GetData() );

    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    //Adds status bar
    QStatusBar *statusbar = new QStatusBar(this);
    ui->verticalLayout->addWidget(statusbar);


    //Disable filter options until a source is loaded
    ui->Btn_Filter->setEnabled(0);
    ui->checkBox_Clip->setEnabled(0);
    ui->checkBox_Shrink->setEnabled(0);
    ui->checkBox_Elevation->setEnabled(0);
    ui->checkBox_Transform->setEnabled(0);

    ui->Btn_Model_Colour->setEnabled(0);
    ui->Btn_Position->setEnabled(0);
    ui->Btn_Remove->setEnabled(0);
    ui->Btn_Reset->setEnabled(0);

    ui->doubleSpinBox->hide(); //Hide uneccesary spin box used for filters
    ui->Lbl_Shrink_Filter->hide();

    ui->verticalWidget_Transform->hide();

    //--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/

    //Connecting slots
    connect( ui->Btn_Change_Background, &QPushButton::released, this, &MainWindow::handleBtn_Change_Background );
    connect( ui->Btn_Model_Colour, &QPushButton::released, this, &MainWindow::handleBtn_Model_Colour );

    connect( ui->Btn_Clear, &QPushButton::released, this, &MainWindow::handleBtn_Clear );
    connect( ui->Btn_Reset, &QPushButton::released, this, &MainWindow::handleBtn_Reset_Actor );
    connect( ui->Btn_Remove, &QPushButton::released, this, &MainWindow::handleBtn_Remove );

    connect( ui->Btn_Cube, &QPushButton::released, this, &MainWindow::handleBtn_Cube );
    connect( ui->Btn_Sphere, &QPushButton::released, this, &MainWindow::handleBtn_Sphere );
    connect( ui->actionFileOpen, &QAction::triggered, this, &MainWindow::handlactionFileOpen );

    connect( ui->Btn_Camera_Reset, &QPushButton::released, this, &MainWindow::handleBtn_Camera_Reset );
    connect( ui->Btn_Position, &QPushButton::released, this, &MainWindow::handleBtn_Change_Position );

    connect( ui->Btn_Filter, &QPushButton::released, this, &MainWindow::handleBtn_Filter );

    connect( ui->Btn_Test, &QPushButton::released, this, &MainWindow::handleBtn_Test );
    connect( ui->Btn_Test2, &QPushButton::released, this, &MainWindow::handleBtn_Test2 );

    connect( ui->comboBox_Actors, &QComboBox::currentTextChanged,this,&MainWindow::New_Actor_Selected );

    connect ( ui->tabWidget, &QTabWidget::currentChanged,this,&MainWindow::Tab_Changed);

    //connecting statusUpdateMessage()
    connect( this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage );

    // Create a cube using a vtkCubeSource
    CubeSource = vtkSmartPointer<vtkCubeSource>::New();
    // Create a cube using a vtkCubeSource
    sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();
}

void MainWindow::NewSource(QString Source_Type) //General source function - need
//Still need to create 1 cube and sphere globally for use (after they are created), hence use of Cube and SphereSource globals
{
    if (Source_Type=="Cube")
    {

        // Create a mapper that will hold the Cube's geometry in a format suitable for rendering
        Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        Source_mapper->SetInputConnection( CubeSource->GetOutputPort() );

        // Create an actor that is used to set the cube's properties for rendering and place it in the window
        Source_actor = vtkSmartPointer<vtkActor>::New();
        Source_actor->SetMapper(Source_mapper);
        Source_actor->GetProperty()->EdgeVisibilityOn();

        Rendered_Cube_Actor_Array.push_back(Source_actor);

        emit statusUpdateMessage( QString("Cube Added!"), 0 );

    }
    if (Source_Type=="Sphere")
    {
        // Create a mapper that will hold the Cube's geometry in a format suitable for rendering
        Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        Source_mapper->SetInputConnection( sphereSource->GetOutputPort() );

        // Create an actor that is used to set the cube's properties for rendering and place it in the window
        Source_actor = vtkSmartPointer<vtkActor>::New();
        Source_actor->SetMapper(Source_mapper);
        Source_actor->GetProperty()->EdgeVisibilityOn();

        Rendered_Sphere_Actor_Array.push_back(Source_actor);

        emit statusUpdateMessage( QString("Sphere Added!"), 0 );
    }
    if (Source_Type=="STL")
    {
        //Read file into Qstring object using QFileDialog::getOpenFileName
        fileName.clear();
        fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));

        //Convert the filename from qstring to a char pointer (char array)
        ba.clear();
        ba = fileName.toLocal8Bit();
        const char *c_str = "";
        c_str = ba.data();

        vtkNew<vtkSTLReader> reader; //Creates a new reader object for the new STL (prevents overwrite issues)
        reader->SetFileName(c_str); //reader object to point to the filename
        reader->Update();

        // Have the vtk mapper point to the file using the vtk reader
        Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        Source_mapper->SetInputConnection(reader->GetOutputPort());

        //Have the actor point to the mapper
        Source_actor = vtkSmartPointer<vtkActor>::New();
        Source_actor->SetMapper(Source_mapper);

        File_Name_Array.push_back(fileName); //Add source file name to array of names for use in filtering (as models are re-rendered)
        Rendered_STL_Actor_Array.push_back(Source_actor); //Add the actor pointer of the STL object to the actor array.

        emit statusUpdateMessage( QString("STL Added!"), 0 );
    }

    if(ui->tabWidget->currentIndex()==0)
    {
        renderer->AddActor(Source_actor);
        renderWindow->Render();
    }
    else if (ui->tabWidget->currentIndex()==1)
    {
        renderer_Tab2->AddActor(Source_actor);
        renderWindow_Tab2->Render();
    }

    //Now that the source, mapper and actor for the desired model have been created, and the actor
    //has been added to the renderer, add the new actor to the drop down box using the "Add_Rendered_Actors_To_Combo"
    //function, and reset the camera

    Add_Rendered_Actors_To_Combo();
    handleBtn_Camera_Reset();
    //Re-enable all appropriate things for currently selected actor

    reset_function();
    ui->Btn_Model_Colour->setEnabled(1);
    ui->Btn_Position->setEnabled(1);
    ui->Btn_Filter->setEnabled(1);
}

void MainWindow::handleBtn_Test()
{

      //vtkSmartPointer<vtkAlgorithm> sphereSource1 = (vtkSmartPointer<vtkAlgorithm>) vtkSmartPointer<vtkSphereSource>::New();

      vtkNew<vtkSphereSource> sphereSource1;
      sphereSource1->Update();
      vtkNew<vtkDelaunay3D> delaunay1;
      delaunay1->SetInputConnection(sphereSource1->GetOutputPort());
      delaunay1->Update();

      vtkNew<vtkSphereSource> sphereSource2;
      sphereSource2->SetCenter(5, 0, 0);
      sphereSource2->Update();

      vtkNew<vtkDelaunay3D> delaunay2;
      delaunay2->SetInputConnection(sphereSource2->GetOutputPort());
      delaunay2->Update();

      vtkNew<vtkAppendFilter> appendFilter;
      appendFilter->AddInputConnection(delaunay1->GetOutputPort());
      appendFilter->AddInputConnection(delaunay2->GetOutputPort());
      appendFilter->Update();

      vtkNew<vtkConnectivityFilter> connectivityFilter;
      connectivityFilter->SetInputConnection(appendFilter->GetOutputPort());
      connectivityFilter->SetExtractionModeToAllRegions();
      connectivityFilter->ColorRegionsOn();
      connectivityFilter->Update();

      ModelData = vtkSmartPointer<vtkAlgorithm>::New();
      ModelData = (vtkSmartPointer<vtkAlgorithm>) connectivityFilter;

      ModelData = Shrink_Filter(ModelData);

      vtkNew<vtkDataSetMapper> mapper;
      mapper->SetInputConnection(ModelData->GetOutputPort());
      mapper->Update();

      vtkNew<vtkActor> actor;
      actor->SetMapper(mapper);

      renderer->AddActor(actor);
      Rendered_Sphere_Actor_Array.push_back(actor);
      renderWindow->Render();
      Add_Rendered_Actors_To_Combo();

}

void MainWindow::handleBtn_Test2()
{
       //vtkNew<vtkCubeSource> CubeSource;
       sphereSource->SetThetaResolution(30);
       sphereSource->SetPhiResolution(15);
       sphereSource->Update();

       ModelData = vtkSmartPointer<vtkAlgorithm> (sphereSource);

       ModelData = Clip_Filter(ModelData);
       vtkNew<vtkDataSetMapper> mapper;
       mapper->SetInputConnection(ModelData->GetOutputPort());
       mapper->Update();

       vtkNew<vtkActor> actor;
       actor->SetMapper(mapper);
       renderer_Tab2->AddActor(actor); // display the sphere

       renderWindow_Tab2->Render();
       Rendered_Sphere_Actor_Array.push_back(actor);
       Add_Rendered_Actors_To_Combo();   
}

void MainWindow::handlactionFileOpen()
{

    if (Rendered_STL_Actor_Array.size()<9)
    {
        NewSource(QString("STL"));
    }
    else
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("Cannot have more than 9 STL models!"));
        warning_box.show();
    }

}

void MainWindow::handleBtn_Cube()
{
    if (Rendered_Cube_Actor_Array.size()<9)
    {
        NewSource(QString("Cube"));
    }
    else
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("Cannot have more than 9 cubes!"));
        warning_box.show();
    }
}

void MainWindow::handleBtn_Sphere()
{
    if (Rendered_Sphere_Actor_Array.size()<9)
    {
        NewSource(QString("Sphere"));
    }
    else
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("Cannot have more than 9 spheres!"));
        warning_box.show();
    }
}

void MainWindow::handleBtn_Model_Colour()
{
    if(ui->comboBox_Actors->currentText() == "")
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("No model selected!"));
        warning_box.show();
    }
    else
    {
        QColor ColourDialog = QColorDialog::getColor();

        Object_RedF=ColourDialog.redF();
        Object_GreenF=ColourDialog.greenF();
        Object_BlueF=ColourDialog.blueF();

        FindActor()->GetProperty()->SetColor(Object_RedF,Object_GreenF,Object_BlueF);
        if(ui->tabWidget->currentIndex()==0)
        {
            renderWindow->Render();
        }
        else if (ui->tabWidget->currentIndex()==1)
        {
            renderWindow_Tab2->Render();
        }
        emit statusUpdateMessage( QString("Model colour changed!"), 0 );
    }




}

void MainWindow::handleBtn_Change_Background()
{
    QColor ColourDialog = QColorDialog::getColor();
    float Red,Green,Blue=0.;
    Red=ColourDialog.redF();
    Green=ColourDialog.greenF();
    Blue=ColourDialog.blueF();

    renderer->SetBackground(Red,Green,Blue);
    renderWindow->Render();

    emit statusUpdateMessage( QString("Background colour changed!"), 0 );
}

void MainWindow::handleBtn_Camera_Reset()
{
    if(ui->tabWidget->currentIndex()==0)
    {
        renderer->ResetCamera();
        renderer->GetActiveCamera()->Azimuth(30);
        renderer->GetActiveCamera()->Elevation(30);
        renderer->ResetCameraClippingRange();
        renderWindow->Render();
    }
    else if (ui->tabWidget->currentIndex()==1)
    {
        renderer_Tab2->ResetCamera();
        renderer_Tab2->GetActiveCamera()->Azimuth(30);
        renderer_Tab2->GetActiveCamera()->Elevation(30);
        renderer_Tab2->ResetCameraClippingRange();
        renderWindow_Tab2->Render();
    }



    emit statusUpdateMessage( QString("Camera reset!"), 0 );
}

void MainWindow::reset_function() //NEEDS UPDATING
{
    if(ui->checkBox_Clip->isChecked()==true)
    {
         ui->checkBox_Clip->setChecked(false);
    }
    if (ui->checkBox_Shrink->isChecked()==true)
    {
        ui->doubleSpinBox->setValue(1);
        ui->doubleSpinBox->hide();
        ui->Lbl_Shrink_Filter->hide();
        ui->checkBox_Shrink->setChecked(false);
    }
    if(ui->checkBox_Elevation->isChecked()==true)
    {
         ui->checkBox_Elevation->setChecked(false);
    }
    if (ui->checkBox_Transform->isChecked()==true)
    {
        ui->verticalWidget_Transform->hide();
        ui->doubleSpinBox_X_Transform->setValue(1);
        ui->doubleSpinBox_Y_Transform->setValue(1);
        ui->doubleSpinBox_Z_Transform->setValue(1);
        ui->checkBox_Transform->setChecked(false);
    }

    ui->checkBox_Clip->setEnabled(1);
    ui->checkBox_Shrink->setEnabled(1);
    ui->checkBox_Elevation->setEnabled(1);
    ui->checkBox_Transform->setEnabled(1);

    ui->Btn_Model_Colour->setEnabled(1);
    ui->Btn_Position->setEnabled(1);
    ui->Btn_Remove->setEnabled(1);
    ui->Btn_Reset->setEnabled(1);

}

void MainWindow::handleBtn_Clear() //Function to clear whole program
{
    //Function should: disable position elements, actor colour picker and filter checkboxes
    //Function should fully clear all source and actor arrays, the rendered actor collection and the rendered actor array
    //Function should also clear drop down menue, and the values on all boxes where values can be entered, including
    //colour pickers

    reset_function();
    //Disable filter options until a source is loaded
    ui->checkBox_Clip->setEnabled(0);
    ui->checkBox_Shrink->setEnabled(0);
    ui->checkBox_Elevation->setEnabled(0);
    ui->checkBox_Transform->setEnabled(0);
    ui->Btn_Model_Colour->setEnabled(0);
    ui->Btn_Position->setEnabled(0);
    ui->Btn_Remove->setEnabled(0);
    ui->Btn_Reset->setEnabled(0);
    ui->Btn_Filter->setEnabled(0);
    ui->doubleSpinBox->hide(); //Hide uneccesary spin box used for filters
    ui->Lbl_Shrink_Filter->hide();
    ui->verticalWidget_Transform->hide(); //Hide uneccesary spin boxes9 used for transform filter.

    renderer->RemoveAllViewProps(); //Remove all currently rendered objects.
    renderWindow->Render();

    renderer_Tab2->RemoveAllViewProps();
    renderWindow_Tab2->Render();

    //Clear the actor array
    Rendered_Cube_Actor_Array.clear();
    Rendered_Sphere_Actor_Array.clear();
    Rendered_STL_Actor_Array.clear();
    File_Name_Array.clear();

    ui->comboBox_Actors->clear();
}

void MainWindow::handleBtn_Change_Position() //Function to change the position of the currently selected actor from the drop down menue
{
    if(ui->comboBox_Actors->currentText() == "")
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("No model selected!"));
        warning_box.show();
    }
    else
    {
        //Using the FindActor function to find the pointer to the actor currently selected from the drop down menue by the user,
        //Set it's position to the values the user has entered into the spin boxes for x, y and z, and then re-render
        FindActor()->SetPosition(ui->doubleSpinBox_X->value(),ui->doubleSpinBox_Y->value(),ui->doubleSpinBox_Z->value());
        if(ui->tabWidget->currentIndex()==0)
        {
            renderWindow->Render();
        }
        else if (ui->tabWidget->currentIndex()==1)
        {
            renderWindow_Tab2->Render();
        }
        emit statusUpdateMessage( QString("Model position changed!"), 0 );
    }
}

void MainWindow::New_Actor_Selected() //Function run whenever user selects one of the rendered actors from the drop down menue
{
    //The function uses the FindActor function to find the pointer to the selected actor, and uses the GetPosition funciton
    //(a member of the actor class) to find the position of the currently selected actor and read it into a 3*1 array
    //called Position, where postion[0] is the x, postion[1] is the y and postion[2] is the z values.
    //The corresponding spin boxes are then updated.

    if (ui->comboBox_Actors->currentText()!="")
    {
        double *Position;
        Position = FindActor()->GetPosition();
        ui->doubleSpinBox_X->setValue(Position[0]);
        ui->doubleSpinBox_Y->setValue(Position[1]);
        ui->doubleSpinBox_Z->setValue(Position[2]);

        reset_function();
    }
}

void MainWindow::Tab_Changed()
{
    reset_function();
    Add_Rendered_Actors_To_Combo();
}

void MainWindow::Add_Rendered_Actors_To_Combo() //Function to add the pointers to all currently rendered actors to respective arrays,   
{                                               //with different arrays for each source type.
    //The function first created an array to store the pointers of all rendered actors, and an actor collection to read all the pointers
    //into initially, using the "GetActors" member function of the renderer class.
    //This collection of actor pointers is then readied for traversal using the "InitTraversal" member function of the vtkActorCollection
    //class. Then, the collection is stepped through for all values, which are read into the Rendered_Actor_Array.

    //This Rendered_Actor_Array is then used to populate the combo box (drop down menue). This is done by comparing every element
    //of the Rendered_Actor_Array to all the elements in thestored actor arrays (e.g. Rendered_Cube_Actor_Array) created when a
    //new source is rendered by the user. This has benifit of there being only one match to each pointer, as such the array the pointer
    //is matched to (e.g. the cube, sphere, or STL arrays) can be used to identify the origional source type. This is needed in the combo
    //box both to display the correct name, and later for use in applying filters.

    //The other function performed is that once the source of the actor is known, the index of the actor pointer in the
    //associated rendered source type specific array (e.g. Rendered_Cube_Actor_Array) is added to the end. Whilst for
    //cubes and spheres this is not particularly useful apart from telling the different cubes and spheres apart (as the cube
    //and sphere are all created from the same source), this added index is particularly useful in the case of STL sources,
    //as the index value of the Rendered_STL_Actor_Array is used to find the correct source (stored in the NAME NEEDED AAAAAAAAAAAAA)
    //array for re-rendering/filtering in other parts of the code.

    std::vector<vtkSmartPointer<vtkActor>> Rendered_Actor_Array;

    vtkActorCollection *Collection = vtkActorCollection::New();

    if(ui->tabWidget->currentIndex()==0)
    {
        Collection = renderer->GetActors();
    }
    else if (ui->tabWidget->currentIndex()==1)
    {
        Collection = renderer_Tab2->GetActors();
    }

    Collection->InitTraversal(); //Initialise actor collection to be sepped through

    while( (Current_actor = Collection->GetNextActor()) )
    {
        Rendered_Actor_Array.push_back(Current_actor); //Add all actors to rendered actor array
    }

    ui->comboBox_Actors->clear(); //Clear current actors drop down box
    QString Index = "";
    QString Entry = "";

    for (int i =0;i<Rendered_Actor_Array.size();i++)
    {
       for (int j=0;j<Rendered_Cube_Actor_Array.size();j++)
       {
           if(Rendered_Actor_Array[i]==Rendered_Cube_Actor_Array[j])
           {
               Index = QString::number(j);
               Entry = "cube " + Index;
               ui->comboBox_Actors->addItem(Entry);

           }
       }
       for (int j=0;j<Rendered_Sphere_Actor_Array.size();j++)
       {
           if(Rendered_Actor_Array[i]==Rendered_Sphere_Actor_Array[j])
           {
               Index = QString::number(j);
               Entry = "sphere " + Index;
               ui->comboBox_Actors->addItem(Entry);
           }
       }
       for (int j=0;j<Rendered_STL_Actor_Array.size();j++)
       {
           if(Rendered_Actor_Array[i]==Rendered_STL_Actor_Array[j])    //Should be [STL,j], so the actual actor can be found using j
                                                                       //This is done by storing the reader of each stl with its actor
                                                                       //when rendering, so once actor is found so is source
           {
               Index = QString::number(j);
               Entry = "STL " + Index;
               ui->comboBox_Actors->addItem(Entry);
           }
       }
       }
}

void MainWindow::handleBtn_Remove()
{
    if(ui->comboBox_Actors->currentText() == "")
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("No model selected!"));
        warning_box.show();
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = warning_box.question(this, "Please select an option", "Are you sure you wish to remove this model?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            if(ui->tabWidget->currentIndex()==0)
            {
                renderer->RemoveActor(FindActor());
            }
            else if (ui->tabWidget->currentIndex()==1)
            {
                renderer_Tab2->RemoveActor(FindActor());
            }

            QString Combo_text = ui->comboBox_Actors->currentText();
            QChar Num = Combo_text.back();
            int Index = Num.digitValue();

            if(ui->comboBox_Actors->currentText().contains("cube"))
            {
                Rendered_Cube_Actor_Array.erase(Rendered_Cube_Actor_Array.begin()+Index);
            }
            else if(ui->comboBox_Actors->currentText().contains("sphere"))
            {
                Rendered_Sphere_Actor_Array.erase(Rendered_Sphere_Actor_Array.begin()+Index);
            }
            else if(ui->comboBox_Actors->currentText().contains("STL"))
            {
                Rendered_STL_Actor_Array.erase(Rendered_STL_Actor_Array.begin()+Index);
                File_Name_Array.erase(File_Name_Array.begin()+Index);
            }
            Add_Rendered_Actors_To_Combo();

            renderWindow->Render();
            renderWindow_Tab2->Render();
            reset_function();
        }
        else
        {

        }
    }


}

void MainWindow::handleBtn_Reset_Actor() //Button to reset selected actor/model
{
    if(ui->comboBox_Actors->currentText() == "")
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(QString("Warning"));
        warning_box.setText(QString("No model selected!"));
        warning_box.show();
    }
    else
    {
        QMessageBox::StandardButton reply;
        reply = warning_box.question(this, "Please select an option", "Are you sure you wish to reset this model?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            QString Combo_text = ui->comboBox_Actors->currentText();
            QChar Num = Combo_text.back();
            int Index = Num.digitValue();
            if(ui->tabWidget->currentIndex()==0)
            {
                renderer->RemoveActor(FindActor());
            }
            else if (ui->tabWidget->currentIndex()==1)
            {
                renderer_Tab2->RemoveActor(FindActor());
            }

            if (Combo_text.contains("cube"))
            {
                Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
                Source_mapper->SetInputConnection( CubeSource->GetOutputPort() );

                // Create an actor that is used to set the cube's properties for rendering and place it in the window
                Source_actor = vtkSmartPointer<vtkActor>::New();
                Source_actor->SetMapper(Source_mapper);
                Source_actor->GetProperty()->EdgeVisibilityOn();

                Rendered_Cube_Actor_Array[Index] = Source_actor;
            }
            else if (Combo_text.contains("sphere"))
            {
                Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
                Source_mapper->SetInputConnection( sphereSource->GetOutputPort() );

                // Create an actor that is used to set the cube's properties for rendering and place it in the window
                Source_actor = vtkSmartPointer<vtkActor>::New();
                Source_actor->SetMapper(Source_mapper);
                Source_actor->GetProperty()->EdgeVisibilityOn();

                Rendered_Sphere_Actor_Array[Index] = Source_actor;
            }
            else if (Combo_text.contains("STL"))
            {
                //Convert the filename from qstring to a char pointer (char array)
                //The filename is stored in the File_Name_Array vector, with the same index as the pointer to the actor of that file.
                //Therefore the index of the STL's actor can be used to find the index of the STL file.
                fileName.clear();
                fileName = File_Name_Array[Index];
                ba.clear();
                ba = fileName.toLocal8Bit();
                const char *c_str = "";
                c_str = ba.data();

                vtkNew<vtkSTLReader> reader;
                reader->SetFileName(c_str); //reader object to point to the filename
                reader->Update();

                Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
                Source_mapper->SetInputConnection( reader->GetOutputPort() );

                // Create an actor that is used to set the cube's properties for rendering and place it in the window
                Source_actor = vtkSmartPointer<vtkActor>::New();
                Source_actor->SetMapper(Source_mapper);
                Source_actor->GetProperty()->EdgeVisibilityOn();

                Rendered_STL_Actor_Array[Index] = Source_actor;
            }
            if(ui->tabWidget->currentIndex()==0)
            {
                renderer->AddActor(Source_actor);
                renderWindow->Render();
            }
            else if (ui->tabWidget->currentIndex()==1)
            {
                renderer_Tab2->AddActor(Source_actor);
                renderWindow_Tab2->Render();
            }
            New_Actor_Selected(); //Re-updates the position box
            reset_function(); //Resets the UI
        }
        else
        {
            //Do nothing
        }
    }
}

vtkSmartPointer<vtkActor> MainWindow::FindActor() //Function to find the currently selected actor from the drop down menue
{
    //The function uses the Qstring in the combo box (drop down menue) to find the pointer to the currently selected actor
    //The function first reads the text into the Combo_text variable, before converting the last element of the string to a
    //Qchar, selecting it using the "back" function, a member function of the QString class. The "digitvalue" member function of
    //the QChar class is then used to read it's numeric value into an integer.

    //This number is the index of the selected actor in the actor array. The function then uses the text in the combo box
    //to find what type of source is being rendered using the actor e.g. "cube", so it knows which actor array to search.
    //The function then returns the vtkSmartPointer found.

    //The function would break if there was no text to analyse or if there was no number, however this function is all back-end code
    //and use should be controlled through enabling/disabling of the correct UI elements, so error control is not strictly needed.

    QString Combo_text = ui->comboBox_Actors->currentText();
    QChar Num = Combo_text.back();
    int Index = Num.digitValue();

    if (Combo_text.contains("cube"))
    {
        return(Rendered_Cube_Actor_Array[Index]);
    }
    else if (Combo_text.contains("sphere"))
    {
         return(Rendered_Sphere_Actor_Array[Index]);
    }
    else if (Combo_text.contains("STL"))
    {
         return(Rendered_STL_Actor_Array[Index]);
    }
    else return(nullptr);
}

vtkSmartPointer<vtkAlgorithm> MainWindow::Shrink_Filter(vtkSmartPointer<vtkAlgorithm> ModelData)
{
    vtkSmartPointer<vtkAlgorithm> Data = ModelData;
    Cube_shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    Cube_shrinkFilter->SetInputConnection(Data->GetOutputPort() );
    Cube_shrinkFilter->SetShrinkFactor(ui->doubleSpinBox->value());
    Cube_shrinkFilter->Update();
    return((vtkSmartPointer<vtkAlgorithm>) Cube_shrinkFilter);
}

vtkSmartPointer<vtkAlgorithm> MainWindow::Clip_Filter(vtkSmartPointer<vtkAlgorithm> ModelData)
{
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(0.0, 0.0, 0.0);
    planeLeft->SetNormal(-1.0, 0.0, 0.0);
    vtkSmartPointer<vtkAlgorithm> Data = ModelData;
    Current_clipFilter= vtkSmartPointer<vtkClipDataSet>::New();
    Current_clipFilter->SetInputConnection( Data->GetOutputPort() ) ;
    Current_clipFilter->SetClipFunction( planeLeft.Get() );
    return ((vtkSmartPointer<vtkAlgorithm>) Current_clipFilter);
}

vtkSmartPointer<vtkAlgorithm> MainWindow::Elevation_Filter(vtkSmartPointer<vtkAlgorithm> ModelData)
{
    vtkElevationFilter *Elevation_Filter = vtkElevationFilter::New();
    Elevation_Filter->SetInputConnection(ModelData->GetOutputPort());
    Elevation_Filter->SetLowPoint(0,-1,0);
    Elevation_Filter->SetHighPoint(0,1,0);

    return ((vtkSmartPointer<vtkAlgorithm>) Elevation_Filter);
}

vtkSmartPointer<vtkAlgorithm> MainWindow::Transform_Filter(vtkSmartPointer<vtkAlgorithm> ModelData)
{
    vtkTransform *aTransfrom = vtkTransform::New();
    aTransfrom->Scale(ui->doubleSpinBox_X_Transform->value(),ui->doubleSpinBox_Y_Transform->value(),ui->doubleSpinBox_Z_Transform->value());

    vtkTransformFilter *test = vtkTransformFilter::New();
    test->SetInputConnection(ModelData->GetOutputPort());
    test->SetTransform(aTransfrom);

    return ((vtkSmartPointer<vtkAlgorithm>) test);
}

void MainWindow::handleBtn_Filter()
{

   if(ui->comboBox_Actors->currentText() == "")
   {
       warning_box.setIcon(warning_box.Information);
       warning_box.setStandardButtons(warning_box.Ok);
       warning_box.setWindowTitle(QString("Warning"));
       warning_box.setText(QString("No model selected!"));
       warning_box.show();
   }
   else
   {

        QString Combo_text = ui->comboBox_Actors->currentText();
        QChar Num = Combo_text.back();
        int Index = Num.digitValue();

        double *Colour;
        Colour = FindActor()->GetProperty()->GetColor();

        double *Position;
        Position = FindActor()->GetPosition();

        ModelData = vtkSmartPointer<vtkAlgorithm>::New();

        if(ui->comboBox_Actors->currentText().contains("cube"))
        {
            ModelData = (vtkSmartPointer<vtkAlgorithm>) CubeSource;
            emit statusUpdateMessage(QString("Source is a cube"), 0 );
            Current_actor = FindActor();
        }
        else if(ui->comboBox_Actors->currentText().contains("sphere"))
        {
            ModelData = (vtkSmartPointer<vtkAlgorithm>) sphereSource;
            emit statusUpdateMessage(QString("Source is a sphere"), 0 );
            Current_actor = FindActor();
        }
        else if(ui->comboBox_Actors->currentText().contains("STL"))
        {
            //Convert the filename from qstring to a char pointer (char array)
            //The filename is stored in the File_Name_Array vector, with the same index as the pointer to the actor of that file.
            //Therefore the index of the STL's actor can be used to find the index of the STL file.
            fileName.clear();
            fileName = File_Name_Array[Index];
            ba.clear();
            ba = fileName.toLocal8Bit();
            const char *c_str = "";
            c_str = ba.data();

            vtkNew<vtkSTLReader> reader;
            reader->SetFileName(c_str); //reader object to point to the filename
            reader->Update();
            ModelData = (vtkSmartPointer<vtkAlgorithm>) reader; //Creates a new pointer to avoid overwrite issues.
            emit statusUpdateMessage(QString("Source is an STL"), 0 );
            Current_actor = FindActor();
        }

        if(ui->tabWidget->currentIndex()==0)
        {
            renderer->RemoveActor(Current_actor);
        }
        else if (ui->tabWidget->currentIndex()==1)
        {
            renderer_Tab2->RemoveActor(Current_actor);
        }



        //Below are if statements for every combination of the four filter checkboxes. The combination of all four
        //checkboxes not having been selected is not needed as in this case the ModelData should remain unchanged.

        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Transform_Filter(ModelData);
        }
        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Elevation_Filter(ModelData);
        }
        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Elevation_Filter(Transform_Filter(ModelData));
        }
        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Clip_Filter(ModelData);
        }
        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Clip_Filter(Transform_Filter(ModelData));
        }
        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Clip_Filter(Elevation_Filter(ModelData));
        }
        if (ui->checkBox_Shrink->isChecked()==false && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Clip_Filter(Elevation_Filter(Transform_Filter(ModelData)));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Shrink_Filter(ModelData);
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Shrink_Filter(Transform_Filter(ModelData));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Shrink_Filter(Elevation_Filter(ModelData));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==false &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Shrink_Filter(Elevation_Filter(Transform_Filter(ModelData)));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Shrink_Filter(Clip_Filter(ModelData));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==false && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Shrink_Filter(Clip_Filter(Transform_Filter(ModelData)));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==false)
        {
            ModelData = Shrink_Filter(Clip_Filter(Elevation_Filter(ModelData)));
        }
        if (ui->checkBox_Shrink->isChecked()==true && ui->checkBox_Clip->isChecked()==true &&
                ui->checkBox_Elevation->isChecked()==true && ui->checkBox_Transform->isChecked()==true)
        {
            ModelData = Shrink_Filter(Clip_Filter(Elevation_Filter(Transform_Filter(ModelData))));
        }

        Source_mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        Source_mapper->SetInputConnection( ModelData->GetOutputPort());

        // Create an actor that is used to set the cube's properties for rendering and place it in the window
        Source_actor = vtkSmartPointer<vtkActor>::New();
        Source_actor->SetMapper(Source_mapper);
        Source_actor->GetProperty()->EdgeVisibilityOn();

        Source_actor->GetProperty()->SetColor(Colour);
        Source_actor->SetPosition(Position[0],Position[1],Position[2]);

        if(ui->tabWidget->currentIndex()==0)
        {
            renderer->AddActor(Source_actor);
            renderWindow->Render();
        }
        else if (ui->tabWidget->currentIndex()==1)
        {
            renderer_Tab2->AddActor(Source_actor);
            renderWindow_Tab2->Render();
        }

        if(ui->comboBox_Actors->currentText().contains("cube"))
        {
            Rendered_Cube_Actor_Array[Index] = Source_actor;
        }
        else if(ui->comboBox_Actors->currentText().contains("sphere"))
        {
            Rendered_Sphere_Actor_Array[Index] = Source_actor;
        }
        else if(ui->comboBox_Actors->currentText().contains("STL"))
        {
            Rendered_STL_Actor_Array[Index] = Source_actor;
        }

        if (ui->checkBox_Shrink->isChecked()==true)
        {
            ui->doubleSpinBox->show();
            ui->Lbl_Shrink_Filter->show();
        }
        else
        {
            ui->doubleSpinBox->hide();
            ui->Lbl_Shrink_Filter->hide();
        }

        if (ui->checkBox_Transform->isChecked()==true)
        {
            ui->verticalWidget_Transform->show();
        }
        else
        {
            ui->verticalWidget_Transform->hide();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//NEED TO SORT STL WHEN FILE NOT SELECTED

//IDEA :  Roatate sliders for objects using actor->rotateX e.g. or rotateZXWY

//NEEDED:

//      function to control which render window is used
//      get rotation and volume/size code from donkun

//Link QApplication::quit(); to x button to check if user wants to quit


