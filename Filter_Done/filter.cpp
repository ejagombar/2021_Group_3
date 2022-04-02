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

}

void filter::reflect(ModelRender *ReflectModel){

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

    ReflectModel->getRenderer()->AddActor(reflectactor);
    //ReflectModel->getRenderer()->AddActor(ReflectModel->getActor());
    ReflectModel->getRenderWindow()->Render();
}


void filter::outLine(ModelRender* OutlineModel){
    outlinepolydata=OutlineModel->getPolyData();
    outlinefilter->SetInputData(outlinepolydata);
    outlinefilter->Update();
    outlinemapper->SetInputConnection(outlinefilter->GetOutputPort());
    outlineactor->SetMapper(outlinemapper);
    outlineactor->GetProperty()->SetColor(0,0,1);
    outlineactor->GetProperty()->SetLineWidth(1.5);
    OutlineModel->getRenderer()->AddActor(outlineactor);
    OutlineModel->getRenderWindow()->Render();
}


void filter::smooth(ModelRender *SmoothModel){

    SmoothModel->getRenderer()->RemoveAllViewProps();

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

    SmoothModel->getRenderer()->AddActor(smoothactor);
    SmoothModel->getRenderWindow()->Render();
}

void filter::smoothadd(ModelRender *SmoothModel){

    //SmoothModel->getRenderer()->RemoveAllViewProps();

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

    SmoothModel->getRenderer()->AddActor(smoothactor);
    SmoothModel->getRenderWindow()->Render();
}

void filter::RemoveFilter(ModelRender *removeModel){

    removeModel->getRenderer()->RemoveAllViewProps();
    /*
    removepolydata=removeModel->getPolyData();
    removemapper->SetInputConnection(removepolydata->GetOutputPort());

    removeactor->SetMapper(removemapper);
    removeModel->getRenderer()->AddActor(removeactor);
    removeModel->getRenderWindow()->Render();*/
    removeModel->RenderingStarts();
}
