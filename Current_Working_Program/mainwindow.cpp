///
/// @file
///

#include "mainwindow.h"
#include "ui_mainwindow.h"

//Header files for model visualisation
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkSphereSource.h>
#include <vtkSTLReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <vtkDataSetMapper.h>

//Header files for filtering
#include <vtkShrinkFilter.h>
#include <vtkClipDataSet.h>
#include <vtkPlane.h>
#include <vtkElevationFilter.h>
#include <vtkTransformFilter.h>
#include <vtkTransform.h>

//Header files for model editing/program operation
//#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <stdio.h>
#include <string.h>
#include <QCloseEvent>
#include <QDesktopServices>

//-------------------------------------------------------------
// EEEE2046 Computing Lab work program
//-------------------------------------------------------------

// Authors      : Ben Richards, Edward Agombar,

// Required
// header
// files        : iostream

// README       :
//              :
//              :

// Restrictions/:
// improvements :
//              :
//              :
//              :
//-------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //------------------------------------------------- Program render setup -----------------------------------------------------------*/

    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );

    // Link the renderWindows to their respective QtVTK widgets in each tab
    ui->qvtkWidget_Tab1->setRenderWindow( renderWindow );
    ui->qvtkWidget_Tab2->setRenderWindow( renderWindow_Tab2 );

    // Create new renderers, and add to their respective render windows
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer_Tab2 = vtkSmartPointer<vtkRenderer>::New();
    ui->qvtkWidget_Tab1->renderWindow()->AddRenderer( renderer );
    ui->qvtkWidget_Tab2->renderWindow()->AddRenderer( renderer_Tab2 );

    // Set backgrounds to default black colour
    renderer->SetBackground( colors->GetColor3d("black").GetData() );
    renderer_Tab2->SetBackground( colors->GetColor3d("black").GetData() );

    // Setup the renderers's cameras
    handleBtn_Camera_Reset();

    //Adds status bar
    QStatusBar *statusbar = new QStatusBar(this);
    ui->verticalLayout_VTK_Widget->addWidget(statusbar);

    //------------------------------------------------ Sources for use in program ---------------------------------------------------------*/

    // Create a cube using a vtkCubeSource
    CubeSource = vtkSmartPointer<vtkCubeSource>::New();
    // Create a cube using a vtkCubeSource
    sphereSource = vtkSmartPointer<vtkSphereSource>::New();
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(15);
    sphereSource->Update();

    //----------------------------------------------- Program setup to default state -------------------------------------------------------*/

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

    ui->verticalWidget_Shrink->hide();
    ui->verticalWidget_Transform->hide();

    //------------------------------------------------------- Slots -------------------------------------------------------------------------*/
    //Connecting slots

    //Slots to render models
    connect( ui->Btn_Cube, &QPushButton::released, this, &MainWindow::handleBtn_Cube );
    connect( ui->Btn_Sphere, &QPushButton::released, this, &MainWindow::handleBtn_Sphere );
    connect( ui->actionFileOpen, &QAction::triggered, this, &MainWindow::handlactionFileOpen );

    //Slots to edit models
    connect( ui->Btn_Position, &QPushButton::released, this, &MainWindow::handleBtn_Change_Position );
    connect( ui->Btn_Model_Colour, &QPushButton::released, this, &MainWindow::handleBtn_Model_Colour );
    connect( ui->Btn_Filter, &QPushButton::released, this, &MainWindow::handleBtn_Filter );
    connect( ui->Btn_Reset, &QPushButton::released, this, &MainWindow::handleBtn_Reset_Actor );
    connect( ui->Btn_Remove, &QPushButton::released, this, &MainWindow::handleBtn_Remove_Actor );

    //Slots to run UI
    connect( ui->Btn_Clear, &QPushButton::released, this, &MainWindow::handleBtn_Clear );
    connect( ui->Btn_Camera_Reset, &QPushButton::released, this, &MainWindow::handleBtn_Camera_Reset );
    connect( ui->Btn_Change_Background, &QPushButton::released, this, &MainWindow::handleBtn_Change_Background );
    connect( ui->actionHelp, &QAction::triggered, this, &MainWindow::Help );
    connect( ui->tabWidget, &QTabWidget::currentChanged,this,&MainWindow::Tab_Changed );
    connect( ui->comboBox_Actors, &QComboBox::currentTextChanged,this,&MainWindow::New_Actor_Selected );
    connect( ui->checkBox_Shrink, &QCheckBox::stateChanged,this,&MainWindow::Shrink_Box_Checked );
    connect( ui->checkBox_Transform, &QCheckBox::stateChanged,this,&MainWindow::Transform_Box_Checked );

    //Connecting the status bar
    connect( this, &MainWindow::statusUpdateMessage, ui->statusbar, &QStatusBar::showMessage );
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

        if(fileName.isEmpty()) //Checks to make sure the user selected a file (it is possible to cancel out of the file selection)
        {
            QMessageBox::StandardButton reply;
            reply = warning_box.question(this, "Please select an option", "Invalid file name or type! Please try again.",QMessageBox::Retry|QMessageBox::Close);

            if (reply == QMessageBox::Retry) //If the user wishes to retry file selection, re run-the function, then quit if successful;
            {
                NewSource(QString("STL"));
                return;
            }
            else if(reply == QMessageBox::Close) //If the user does not wish to continue, quit the function so there is not an error
            {
                return;
            }
        }

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

void MainWindow::handlactionFileOpen() //Function to render an STL model from a file
{
    //Checks to see if STL limit has been reached, if it has not, render a new STL using the NewSource function.
    //If it has, inform the user and exit function.
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

void MainWindow::handleBtn_Cube()//Function to render a cube
{
    //Checks to see if cube limit has been reached, if it has not, render a new cube using the NewSource function.
    //If it has, inform the user and exit function.
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

void MainWindow::handleBtn_Sphere() //Function to render a sphere
{
    //Checks to see if sphere limit has been reached, if it has not, render a new sphere using the NewSource function.
    //If it has, inform the user and exit function.
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

void MainWindow::handleBtn_Model_Colour() //Button to change the colour of the currently selected model
{
    // The function checks if the user has selected a model (a.k.a. if the drop down menue is not empty), and then
    //uses the built in QColorDialog function (Qt) to get the user to pick a colour, and then update the selected
    //model to this colour.

    //NOTE! if the elevation filter is applied, the colour change will not be visible until this filter is removed.

    if(Combo_Check(QString("Warning"),QString("No model selected!")))
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

void MainWindow::handleBtn_Change_Background() //Function to change backround to colour selected from colour picker by user
{
    // The function checks if the user has selected a model (a.k.a. if the drop down menue is not empty), and then
    //uses the built in QColorDialog function (Qt) to get the user to pick a colour, and then update the background of the tab
    //currently selected by the user.

    QColor ColourDialog = QColorDialog::getColor();
    float Red,Green,Blue=0.;
    Red=ColourDialog.redF();
    Green=ColourDialog.greenF();
    Blue=ColourDialog.blueF();

    if(ui->tabWidget->currentIndex()==0)
    {
        renderer->SetBackground(Red,Green,Blue);
        renderWindow->Render();
    }
    else if (ui->tabWidget->currentIndex()==1)
    {
        renderer_Tab2->SetBackground(Red,Green,Blue);
        renderWindow_Tab2->Render();
    }
    emit statusUpdateMessage( QString("Background colour changed!"), 0 );
}

void MainWindow::handleBtn_Camera_Reset() //Function to reset camera to default position
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
}

void MainWindow::reset_function() //Function to reset UI to default state
{
    if(ui->checkBox_Clip->isChecked()==true)
    {
         ui->checkBox_Clip->setChecked(false);
    }
    if (ui->checkBox_Shrink->isChecked()==true)
    {
        ui->doubleSpinBox->setValue(1);
        ui->verticalWidget_Shrink->hide();
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

void MainWindow::handleBtn_Clear() //Function to clear whole program if user wants to
{
    //Function disables position elements, actor colour picker and filter checkboxes, fully clears all source and actor
    //arrays, the rendered actor collection and the rendered actor array. It also clears the drop down menue and both tabs'
    //renderers.

    QMessageBox::StandardButton reply;
    reply = warning_box.question(this, "Please select an option", "Are you sure you wish to clear? This will reset both tabs completely.",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
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

        //Remove all currently rendered objects.
        renderer->RemoveAllViewProps();
        renderWindow->Render();
        renderer_Tab2->RemoveAllViewProps();
        renderWindow_Tab2->Render();

        //Clear the actor arrays
        Rendered_Cube_Actor_Array.clear();
        Rendered_Sphere_Actor_Array.clear();
        Rendered_STL_Actor_Array.clear();
        File_Name_Array.clear();

        //Clear the drop down menue
        ui->comboBox_Actors->clear();
    }
    else if (reply == QMessageBox::No)
    {
        //Do nothing
    }


}

void MainWindow::handleBtn_Change_Position() //Function to change the position of the currently selected actor from the drop down menue
{
    if(Combo_Check(QString("Warning"),QString("No model selected!")))
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
    //(a member function of the actor class) to find the position of the currently selected actor and read it into a 3*1 array
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

void MainWindow::Tab_Changed() //Function run whenever the user selecs a different tab to update UI.
{
    reset_function();
    Add_Rendered_Actors_To_Combo();
}

void MainWindow::Add_Rendered_Actors_To_Combo() //Function to add the pointers to all currently rendered actors to respective arrays
{
    //The function first creates an array to store the pointers of all rendered actors, and an actor collection to read all the pointers
    //into initially, using the "GetActors" member function of the renderer class.
    //This collection of actor pointers is then readied for traversal using the "InitTraversal" member function of the vtkActorCollection
    //class. Then, the collection is stepped through for all values, which are read into the Rendered_Actor_Array.

    //This Rendered_Actor_Array is then used to populate the combo box (drop down menue). This is done by comparing every element
    //of the Rendered_Actor_Array to all the elements in the stored actor arrays (e.g. Rendered_Cube_Actor_Array) created when a
    //new source is rendered by the user. This has benifit of there being only one match to each pointer, as such the array the pointer
    //is matched to (e.g. the cube, sphere, or STL arrays) can be used to identify the origional source type. This is needed in the combo
    //box both to display the correct name, and later for use in applying filters.

    //The other function performed is that once the source type of the actor is known, the index of the actor pointer in the
    //associated rendered source type specific array (e.g. Rendered_Cube_Actor_Array) is added to the end. Whilst for
    //cubes and spheres this is not particularly useful apart from telling the different cubes and spheres apart (as the cube
    //and sphere are all created from the same source), this added index is particularly useful in the case of STL sources,
    //as the index value of the Rendered_STL_Actor_Array is used to find the correct source (stored in "File_Name_Array")
    //for re-rendering/filtering in other parts of the code.

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

void MainWindow::handleBtn_Remove_Actor() //Function to remove the model selected by the user if remove button pressed and user agrees to remove
{
    if(Combo_Check(QString("Warning"),QString("No model selected!")))
    {
        QMessageBox::StandardButton reply;
        reply = warning_box.question(this, "Please select an option", "Are you sure you wish to remove this model?",QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {   //Remove from renderer
            if(ui->tabWidget->currentIndex()==0)
            {
                renderer->RemoveActor(FindActor());
            }
            else if (ui->tabWidget->currentIndex()==1)
            {
                renderer_Tab2->RemoveActor(FindActor());
            }

            //Get the source type and actor array index from combo box
            QString Combo_text = ui->comboBox_Actors->currentText();
            QChar Num = Combo_text.back();
            int Index = Num.digitValue();

            //Remove the relevant actor from the releval array
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
    if(Combo_Check(QString("Warning"),QString("No model selected!")))
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
    ///
    ///The function uses the Qstring in the combo box (drop down menue) to find the pointer to the currently selected actor
    ///The function first reads the text into the Combo_text variable, before converting the last element of the string to a
    ///Qchar, selecting it using the "back" function, a member function of the QString class. The "digitvalue" member function of
    ///the QChar class is then used to read it's numeric value into an integer.

    ///This number is the index of the selected actor in it's rendered actor array. The function then uses the text in the combo box
    ///to find what type of source is being rendered using the actor e.g. "cube", so it knows which actor array to search.
    ///The function then returns the vtkSmartPointer found.

    ///The function would break if there was no text to analyse or if there was no number, however this function is all back-end code
    ///and use should be controlled through UI elements such as messageboxes to prevent misuse, so error control is not strictly needed.
    ///
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
    vtkSmartPointer<vtkShrinkFilter> Current_shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
    Current_shrinkFilter->SetInputConnection(Data->GetOutputPort() );
    Current_shrinkFilter->SetShrinkFactor(ui->doubleSpinBox->value());
    Current_shrinkFilter->Update();
    return((vtkSmartPointer<vtkAlgorithm>) Current_shrinkFilter);
}

vtkSmartPointer<vtkAlgorithm> MainWindow::Clip_Filter(vtkSmartPointer<vtkAlgorithm> ModelData)
{
    vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(0.0, 0.0, 0.0);
    planeLeft->SetNormal(-1.0, 0.0, 0.0);
    vtkSmartPointer<vtkAlgorithm> Data = ModelData;
    vtkSmartPointer<vtkClipDataSet> Current_clipFilter= vtkSmartPointer<vtkClipDataSet>::New();
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

void MainWindow::handleBtn_Filter() //function to apply filters selected by the user to the currently selected model
{
   if(Combo_Check(QString("Warning"),QString("No model selected!")))
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
            Current_actor = FindActor();
        }
        else if(ui->comboBox_Actors->currentText().contains("sphere"))
        {
            ModelData = (vtkSmartPointer<vtkAlgorithm>) sphereSource;
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
            ui->verticalWidget_Shrink->show();
        }
        else
        {
            ui->verticalWidget_Shrink->hide();
        }

        if (ui->checkBox_Transform->isChecked()==true)
        {
            ui->verticalWidget_Transform->show();
        }
        else
        {
            ui->verticalWidget_Transform->hide();
        }
        emit statusUpdateMessage(QString("Filters applied!"), 0 );
    }
}

bool MainWindow::Combo_Check(QString Title, QString Message) //Function to check if the combo box is empty
{
    //If the combo box is empty, display an information message box with the title and message passed to this function when called.
    if(ui->comboBox_Actors->currentText() == "")
    {
        warning_box.setIcon(warning_box.Information);
        warning_box.setStandardButtons(warning_box.Ok);
        warning_box.setWindowTitle(Title);
        warning_box.setText(Message);
        warning_box.show();
        return(0);
    }
    else
    {
        return(1);
    }
}

void MainWindow::Shrink_Box_Checked() //Function to handle displaying the appropriate UI elemts when the shrink checkbox is checked
{
    if(ui->checkBox_Shrink->isChecked())
    {
        ui->verticalWidget_Shrink->show();
    }
    else if(ui->checkBox_Shrink->isChecked() != 1)
    {
        ui->verticalWidget_Shrink->hide();
    }
}

void MainWindow::Transform_Box_Checked() //Function to handle displaying the appropriate UI elemts when the transform checkbox is checked
{
    if(ui->checkBox_Transform->isChecked())
    {
        ui->verticalWidget_Transform->show();
    }
    else if(ui->checkBox_Transform->isChecked() != 1)
    {
        ui->verticalWidget_Transform->hide();
    }
}

void MainWindow::Help() //Function to connect the help button to help webpage
{
    QDesktopServices::openUrl(QUrl("https://ejagombar.github.io/2021_Group_3/", QUrl::TolerantMode));
}

void MainWindow::closeEvent(QCloseEvent* event) //Function which runs when user closes program to check
{
    //Checks if the user wishes to exit, if yes the program closes, if not the program exits this function
    QMessageBox::StandardButton reply;
    reply = warning_box.question(this, "Please select an option", "Are you sure you wish quit?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        event->accept();//Quits the program
    }
    if (reply == QMessageBox::No)
    {
        event->ignore(); //Ignores the close button press
    }
}

MainWindow::~MainWindow() //Destructor function called when the program terminates
{
    delete ui;
}

//NEEDED:
//          :Comment code + Doxygen + Rearrange function layout
//          :Make transform fit to actor size? try y axis?
//          :In readme discuss how "actor", "mapper" refered to interchangable as pointer or just the thing itself - disambiguation section
//          :Comment filter function(s)
//          : limit of 9 could be upgraded to 99 by selecting back 2 digits easily but 9 reasonable (report)

