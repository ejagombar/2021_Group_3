#include "filter.h"


filter::filter(){

    reflectfilter=vtkSmartPointer<vtkReflectionFilter>::New();
    reflectpolydata=vtkSmartPointer<vtkPolyData>::New();
    reflectdataset=vtkSmartPointer<vtkDataSetMapper>::New();

    outlineactor = vtkSmartPointer<vtkActor>::New();
    outlinemapper=vtkSmartPointer<vtkPolyDataMapper>::New();
    outlinefilter=vtkSmartPointer<vtkOutlineFilter>::New();
    outlinepolydata=vtkSmartPointer<vtkPolyData>::New();

    smoothfilter = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    smoothpolydata = vtkSmartPointer<vtkPolyData> ::New();
    smoothmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    inputmapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    smoothdelaunay = vtkSmartPointer<vtkDelaunay2D>::New();
    smoothnormals = vtkSmartPointer<vtkPolyDataNormals> ::New();
    smoothactor =  vtkSmartPointer<vtkActor> ::New();

    removeactor = vtkSmartPointer<vtkActor>::New();
    removemapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    removepolydata=vtkSmartPointer<vtkPolyData>::New();

    trianglefilter = vtkSmartPointer<vtkTriangleFilter>::New();
    calcFA = vtkSmartPointer< vtkMassProperties >::New();
    calcFV = vtkSmartPointer< vtkMassProperties >::New();

    shrinkfilter = vtkSmartPointer<vtkShrinkFilter>::New();
    shrinkpolydata = vtkSmartPointer<vtkPolyData>::New();
    shrinkdataset =vtkSmartPointer<vtkDataSetMapper>::New();

    clipfilter=vtkSmartPointer<vtkClipDataSet> ::New();
    clipdataset=vtkSmartPointer<vtkDataSetMapper> ::New();  //Initialize required functions and variables

    //transform=vtkSmartPointer<vtkTransform>::New();
    //transpolydata=vtkSmartPointer<vtkPolyData>::New();
}

void filter::reflect(ModelRender *ReflectModel,vtkSmartPointer<vtkRenderer> renderer){

    reflectpolydata= ReflectModel->getPolyData();
    reflectfilter->SetInputData(reflectpolydata);

    reflectfilter->CopyInputOff();
    reflectfilter->Update();

    vtkSmartPointer<vtkDataSetMapper> reflectmapper =vtkSmartPointer<vtkDataSetMapper> ::New();
    reflectmapper->SetInputConnection(reflectfilter->GetOutputPort());

    vtkSmartPointer<vtkActor> reflectactor=vtkSmartPointer<vtkActor>::New();
    reflectactor->SetMapper(reflectmapper);

    vtkSmartPointer<vtkNamedColors> colors =vtkSmartPointer<vtkNamedColors>::New();
    reflectactor->GetProperty()->SetColor(colors->GetColor3d("Gray").GetData());

    renderer->AddActor(reflectactor);
}

double filter::calcA(ModelRender* calcModel)
{
    trianglefilter->SetInputData(calcModel->getPolyData());
    trianglefilter->Update();

    calcFA->SetInputData(trianglefilter->GetOutput());
    calcFA->Update();

    area = calcFA->GetVolume();
    return area;
}

double filter::calcV(ModelRender* calcModel)
{
    trianglefilter->SetInputData(calcModel->getPolyData());
    trianglefilter->Update();

    calcFV->SetInputData(trianglefilter->GetOutput());
    calcFV->Update();

    vol = calcFV->GetSurfaceArea();
    return vol;
}

void filter::outLine(ModelRender* OutlineModel, vtkSmartPointer<vtkRenderer> renderer, float x, float y, float z){
    outlinepolydata=OutlineModel->getPolyData();
    outlinefilter->SetInputData(outlinepolydata);
    outlinefilter->Update();
    outlinemapper->SetInputConnection(outlinefilter->GetOutputPort());
    outlineactor->SetMapper(outlinemapper);
    outlineactor->GetProperty()->SetColor(0,0,1);
    outlineactor->GetProperty()->SetLineWidth(1.5);
    outlineactor->SetPosition(x,y,z);
    renderer->AddActor(outlineactor);
}


void filter::smooth(ModelRender *SmoothModel,vtkSmartPointer<vtkRenderer> renderer){

    renderer->RemoveAllViewProps();
    smoothdelaunay->SetInputData(SmoothModel->getPolyData());
    smoothdelaunay->Update();
    smoothfilter->SetInputConnection(smoothdelaunay->GetOutputPort());
    smoothfilter->SetNumberOfIterations(20);
    smoothfilter->SetRelaxationFactor(0.5);
    smoothfilter->Update();

    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(smoothfilter->GetOutputPort());
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();
    smoothmapper->SetInputConnection(normalGenerator->GetOutputPort());
    smoothactor->SetMapper(smoothmapper);

    renderer->AddActor(smoothactor);
}

void filter::smoothadd(ModelRender *SmoothModel,vtkSmartPointer<vtkRenderer> renderer){

    smoothdelaunay->SetInputData(SmoothModel->getPolyData());
    smoothdelaunay->Update();
    smoothfilter->SetInputConnection(smoothdelaunay->GetOutputPort());
    smoothfilter->SetNumberOfIterations(20);

    smoothfilter->SetRelaxationFactor(0.5);
    smoothfilter->Update();
    vtkSmartPointer<vtkPolyDataNormals> normalGenerator = vtkSmartPointer<vtkPolyDataNormals>::New();
    normalGenerator->SetInputConnection(smoothfilter->GetOutputPort());
    normalGenerator->ComputePointNormalsOn();
    normalGenerator->ComputeCellNormalsOn();
    normalGenerator->Update();
    smoothmapper->SetInputConnection(normalGenerator->GetOutputPort());
    smoothactor->SetMapper(smoothmapper);

    renderer->AddActor(smoothactor);
}

void filter::shrinkFilter(ModelRender *ShrinkModel,vtkSmartPointer<vtkRenderer> renderer){
   shrinkpolydata=ShrinkModel->getPolyData();
   shrinkfilter->SetInputData(shrinkpolydata);

   shrinkfilter->SetShrinkFactor(.5);

   shrinkfilter->Update();
   shrinkdataset->SetInputConnection(shrinkfilter->GetOutputPort());
   ShrinkModel->getActor()->SetMapper(shrinkdataset);

   renderer->AddActor(ShrinkModel->getActor());
}

void filter::clipFilter(ModelRender *ClipModel,
                        vtkSmartPointer<vtkRenderer> renderer){
    vtkSmartPointer<vtkPlane>plane=vtkSmartPointer<vtkPlane>::New();
    plane ->SetOrigin(ClipModel->getPolyData()->GetCenter());
    plane->SetNormal(0.0,-1.0,0.0);
    clipfilter->SetInputData(ClipModel->getPolyData());
    clipfilter->SetClipFunction(plane.Get());
    clipfilter->Update();
    clipdataset->SetInputConnection(clipfilter->GetOutputPort());
    ClipModel->getActor()->SetMapper(clipdataset);
    renderer->AddActor(ClipModel->getActor());
}

void filter::RemoveFilter(ModelRender *removeModel,vtkSmartPointer<vtkRenderer> renderer){
    renderer->RemoveAllViewProps();
}



















