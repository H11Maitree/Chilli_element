from PIL import Image 
import numpy as np
import coremltools 
print(type(Image.open('16.jpg')))
ar=(np.array(Image.open('16.jpg')))
print(ar.shape)
model = coremltools.models.MLModel('ColourCheck.mlmodel')
falseColour = Image.open('16.jpg') 
print(model.get_spec())
trueColour=Image.open('14.jpg') 
print(model.predict({'image': trueColour})['classLabel'])
print(model.predict({'image': falseColour})['classLabel'])