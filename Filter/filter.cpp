#include "filter.h"

Filter::Filter()
{
    /***************Outline filter************************/
    outlineactor = vtkSmartPointer<vtkActor>::New() ;
    outlinemapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    outlinefilter=vtkSmartPointer<vtkOutlineFilter>::New();
    outlinepolydata=vtkSmartPointer<vtkPolyData>::New();

    /****************shrink filter***********************/
    shrinkfilter = vtkSmartPointer<vtkShrinkFilter>::New();
    shrinkpolydata = vtkSmartPointer<vtkPolyData>::New();
    shrinkdataset =vtkSmartPointer<vtkDataSetMapper>::New();
    /****************smooth filter*****************************/
    smoothfilter = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    smoothpolydata = vtkSmartPointer<vtkPolyData> ::New();
    smoothmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    inputmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    smoothdelaunay = vtkSmartPointer<vtkDelaunay2D>::New();
    smoothnormals = vtkSmartPointer<vtkPolyDataNormals> ::New();
    smoothactor =  vtkSmartPointer<vtkActor> ::New();

    /***************clip filter*******************************/
    clipfilter=vtkSmartPointer<vtkClipDataSet> ::New();
    clipdataset=vtkSmartPointer<vtkDataSetMapper> ::New();
    /***************reflection filter*************************/
    reflectfilter=vtkSmartPointer<vtkReflectionFilter>::New() ;
    reflectpolydata=vtkSmartPointer<vtkPolyData>::New();
    reflectdataset=vtkSmartPointer<vtkDataSetMapper>::New();
    /***************Curavture filter**************************/
    curvaturefilter=vtkSmartPointer<vtkCurvatures>::New();
    scalarbar=vtkSmartPointer<vtkScalarBarActor>::New();
    lut=vtkSmartPointer<vtkColorTransferFunction> ::New();
    colorseries=vtkSmartPointer<vtkColorSeries> ::New();
    curvaturemapper=  vtkSmartPointer<vtkPolyDataMapper> ::New();
    curvaturepoly =vtkSmartPointer<vtkPolyData>::New();
    curvatureactor=vtkSmartPointer<vtkActor>::New();
}

void Filter::outLineFilter(mediator* OutlineModel){
    outlinepolydata=OutlineModel->getPolyData();
    outlinefilter->SetInputData(outlinepolydata);
    outlinefilter->Update();
    outlinemapper->SetInputConnection(outlinefilter->GetOutputPort());
    outlineactor->SetMapper(outlinemapper);
    outlineactor->GetProperty()->SetColor(1,0,0);
    outlineactor->GetProperty()->SetLineWidth(1.5);
    OutlineModel->getRenderer()->AddActor(outlineactor);
    OutlineModel->getRenderWindow()->Render();
}

void Filter::shrinkFilter(mediator *ShrinkModel){

   // reset filter
   ShrinkModel->getRenderer()->RemoveAllViewProps();
   shrinkpolydata=ShrinkModel->getPolyData();
   shrinkfilter->SetInputData(shrinkpolydata);

   // shrink factor 0-1, the smaller the factor the greater the shrinkage
   shrinkfilter->SetShrinkFactor(.5);

   shrinkfilter->Update();
   shrinkdataset->SetInputConnection(shrinkfilter->GetOutputPort());
   ShrinkModel->getActor()->SetMapper(shrinkdataset);
   //rendering
   ShrinkModel->getRenderer()->AddActor(ShrinkModel->getActor());
   ShrinkModel->getRenderWindow()->Render();

}


void Filter::smoothFilter(mediator *SmoothModel){

      //get poly data from model
      smoothdelaunay->SetInputData(SmoothModel->getPolyData());
      smoothdelaunay->Update();
      smoothfilter->SetInputConnection(smoothdelaunay->GetOutputPort());
      smoothfilter->SetNumberOfIterations(15);
      // the larger the factor the smoother the model
      smoothfilter->SetRelaxationFactor(0.1);
      //stop smoothing the edge
      smoothfilter->FeatureEdgeSmoothingOff();
      smoothfilter->BoundarySmoothingOn();
      smoothfilter->Update();

      // Update normals on smoothed PolyData
      vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
      normalGenerator->SetInputConnection(smoothfilter->GetOutputPort());
      normalGenerator->ComputePointNormalsOn();
      normalGenerator->ComputeCellNormalsOn();
      normalGenerator->Update();
      smoothmapper->SetInputConnection(normalGenerator->GetOutputPort());
      smoothactor->SetMapper(smoothmapper);
      //rendering
      SmoothModel->getRenderer()->AddActor(smoothactor);
      SmoothModel->getRenderWindow()->Render();

}


void Filter::clipFilter(mediator *ClipModel){
    //reset filter
    ClipModel->getRenderer()->RemoveAllViewProps();
    vtkSmartPointer<vtkPlane>plane=vtkSmartPointer<vtkPlane>::New();
    //set the origin
    plane ->SetOrigin(ClipModel->getPolyData()->GetCenter());
    //set the normal
    plane->SetNormal(0.0,0.1,1.0);

    clipfilter->SetInputData(ClipModel->getPolyData());
    //start clipping
    clipfilter->SetClipFunction(plane.Get());
    clipfilter->Update();
    clipdataset->SetInputConnection(clipfilter->GetOutputPort());
    //rendering
    ClipModel->getActor()->SetMapper(clipdataset);
    ClipModel->getRenderer()->AddActor(ClipModel->getActor());
    ClipModel->getRenderWindow()->Render();
}


void Filter::reflectFilter(mediator *ReflectModel){

   ReflectModel->getRenderer()->RemoveAllViewProps();

   reflectpolydata= ReflectModel->getPolyData();
   reflectfilter->SetInputData(reflectpolydata);
   //copy the model
   reflectfilter->CopyInputOff();
   reflectfilter->Update();

   vtkSmartPointer<vtkDataSetMapper> reflectmapper =vtkSmartPointer<vtkDataSetMapper> ::New();
   reflectmapper->SetInputConnection(reflectfilter->GetOutputPort());

   vtkSmartPointer<vtkActor> reflectactor=vtkSmartPointer<vtkActor>::New();
   reflectactor->SetMapper(reflectmapper);

   vtkSmartPointer<vtkNamedColors> colors =vtkSmartPointer<vtkNamedColors>::New();
   reflectactor->GetProperty()->SetColor(colors->GetColor3d("Mint").GetData());

   //rendering
   ReflectModel->getRenderer()->AddActor(reflectactor);
   ReflectModel->getRenderer()->AddActor(ReflectModel->getActor());
   ReflectModel->getRenderWindow()->Render();
}


void Filter::curvatureFilter(mediator *curvatureModel){
     //get poly data from Model
     curvatureModel->getRenderer()->RemoveAllViewProps();
     curvaturepoly=curvatureModel->getPolyData();
     curvaturefilter->SetInputData(curvaturepoly);
     //set filter
     curvaturefilter->SetCurvatureTypeToMinimum();
     curvaturefilter->SetCurvatureTypeToMaximum();
     curvaturefilter->SetCurvatureTypeToGaussian();
     curvaturefilter->SetCurvatureTypeToMean();
     curvaturefilter->Update();
     // Build a lookup table
     double scalarRange[2];
     curvaturefilter->GetOutput()->GetScalarRange(scalarRange);
     int scheme = 16;
     colorseries->SetColorScheme(scheme);
     lut->SetColorSpaceToHSV();
     // Use a color series to create a transfer function
     int numColors = colorseries->GetNumberOfColors();
     for (int i = 0; i < numColors; i++)
         {
             vtkColor3ub color = colorseries->GetColor(i);
             double dColor[3];
             dColor[0] = static_cast<double>(color[0]) / 255.0;
             dColor[1] = static_cast<double>(color[1]) / 255.0;
             dColor[2] = static_cast<double>(color[2]) / 255.0;
             double t = scalarRange[0] +
                 (scalarRange[1] - scalarRange[0]) / (numColors - 1) * i;
             lut->AddRGBPoint(t, dColor[0], dColor[1], dColor[2]);
         }

     curvaturemapper->SetInputConnection(curvaturefilter->GetOutputPort());
     curvaturemapper->SetLookupTable(lut);
     curvaturemapper->SetScalarRange(scalarRange);
     curvatureactor->SetMapper(curvaturemapper);
     // Create a scalar bar
     scalarbar->SetLookupTable(curvaturemapper->GetLookupTable());
     scalarbar->SetTitle(curvaturefilter->GetOutput()->GetPointData()->GetScalars()->GetName());
     scalarbar->UnconstrainedFontSizeOn();
     scalarbar->SetNumberOfLabels(5);
     //Rendering
     curvatureModel->getRenderer()->AddActor(curvatureactor);
     curvatureModel->getRenderer()->AddActor(scalarbar);
     curvatureModel->getRenderWindow()->Render();

}

void Filter::resetFilter(mediator *resetModel){

    resetModel->getRenderer()->RemoveAllViewProps();

}




























