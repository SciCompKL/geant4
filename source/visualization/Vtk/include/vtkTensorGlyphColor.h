#include "CommonHeader.h"

/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkTensorGlyphColor.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkTensorGlyphColor
 * @brief   scale and orient glyph(s) according to eigenvalues and eigenvectors of symmetrical part of tensor
 *
 * vtkTensorGlyphColor is a filter that copies a geometric representation
 * (specified as polygonal data) to every input point. The geometric
 * representation, or glyph, can be scaled and/or rotated according to
 * the tensor at the input point. Scaling and rotation is controlled
 * by the eigenvalues/eigenvectors of the symmetrical part of the tensor
 * as follows:
 * For each tensor, the eigenvalues (and associated eigenvectors) are sorted
 * to determine the major, medium, and minor eigenvalues/eigenvectors.
 * The eigenvalue decomposition only makes sense for symmetric tensors,
 * hence the need to only consider the symmetric part of the tensor, which is
 * 1/2 (T + T.transposed()).
 *
 * If the boolean variable ThreeGlyphs is not set the major eigenvalue
 * scales the glyph in the x-direction, the medium in the y-direction,
 * and the minor in the z-direction. Then, the glyph is rotated so
 * that the glyph's local x-axis lies along the major eigenvector,
 * y-axis along the medium eigenvector, and z-axis along the minor.
 *
 * If the boolean variable ThreeGlyphs is set three glyphs are produced,
 * each of them oriented along an eigenvector and scaled according to the
 * corresponding eigenvector.
 *
 * If the boolean variable Symmetric is set each glyph is mirrored (2 or 6
 * glyphs will be produced)
 *
 * The x-axis of the source glyph will correspond to the eigenvector
 * on output. Point (0,0,0) in the source will be placed in the data point.
 * Variable Length will normally correspond to the distance from the
 * origin to the tip of the source glyph along the x-axis,
 * but can be changed to produce other results when Symmetric is on,
 * e.g. glyphs that do not touch or that overlap.
 *
 * Please note that when Symmetric is false it will generally be better
 * to place the source glyph from (-0.5,0,0) to (0.5,0,0), i.e. centred
 * at the origin. When symmetric is true the placement from (0,0,0) to
 * (1,0,0) will generally be more convenient.
 *
 * A scale factor is provided to control the amount of scaling. Also, you
 * can turn off scaling completely if desired. The boolean variable
 * ClampScaling controls the maximum scaling (in conjunction with
 * MaxScaleFactor.) This is useful in certain applications where
 * singularities or large order of magnitude differences exist in
 * the eigenvalues.
 *
 * If the boolean variable ColorGlyphs is set to true the glyphs are
 * colored.  The glyphs can be colored using the input scalars
 * (SetColorModeToScalars), which is the default, or colored using the
 * eigenvalues (SetColorModeToEigenvalues).
 *
 * Another instance variable, ExtractEigenvalues, has been provided to
 * control extraction of eigenvalues/eigenvectors. If this boolean is
 * false, then eigenvalues/eigenvectors are not extracted, and the
 * columns of the tensor are taken as the eigenvectors (the norm of
 * column, always positive, is the eigenvalue).  This allows
 * additional capability over the vtkGlyph3D object. That is, the
 * glyph can be oriented in three directions instead of one.
 *
 * @par Thanks:
 * Thanks to Jose Paulo Moitinho de Almeida for enhancements.
 *
 * @sa
 * vtkGlyph3D vtkPointLoad vtkHyperStreamline
*/

#ifndef vtkTensorGlyphColor_h
#define vtkTensorGlyphColor_h

#include "vtkFiltersCoreModule.h" // For export macro
#include "vtkPolyDataAlgorithm.h"

class VTKFILTERSCORE_EXPORT vtkTensorGlyphColor : public vtkPolyDataAlgorithm
{
public:
  vtkTypeMacro(vtkTensorGlyphColor,vtkPolyDataAlgorithm)
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Construct object with scaling on and scale factor 1.0. Eigenvalues are
   * extracted, glyphs are colored with input scalar data, and logarithmic
   * scaling is turned off.
   */
  static vtkTensorGlyphColor *New();

  //@{
  /**
   * Specify the geometry to copy to each point.
   * Note that this method does not connect the pipeline. The algorithm will
   * work on the input data as it is without updating the producer of the data.
   * See SetSourceConnection for connecting the pipeline.
   */
  void SetSourceData(vtkPolyData *source);
  vtkPolyData *GetSource();
  //@}

  //@{
  /**
   * Specify a source object at a specified table location. New style.
   * Source connection is stored in port 1. This method is equivalent
   * to SetInputConnection(1, id, outputPort).
   */
  void SetSourceConnection(int id, vtkAlgorithmOutput* algOutput);
  void SetSourceConnection(vtkAlgorithmOutput* algOutput)
  {
      this->SetSourceConnection(0, algOutput);
  }
  //@}

  //@{
  /**
   * Turn on/off scaling of glyph with eigenvalues.
   */
  vtkSetMacro(Scaling,vtkTypeBool);
  vtkGetMacro(Scaling,vtkTypeBool);
  vtkBooleanMacro(Scaling,vtkTypeBool);
  //@}

  //@{
  /**
   * Specify scale factor to scale object by. (Scale factor always affects
   * output even if scaling is off.)
   */
  vtkSetMacro(ScaleFactor,G4double);
  vtkGetMacro(ScaleFactor,G4double);
  //@}

  //@{
  /**
   * Turn on/off drawing three glyphs
   */
  vtkSetMacro(ThreeGlyphs,vtkTypeBool);
  vtkGetMacro(ThreeGlyphs,vtkTypeBool);
  vtkBooleanMacro(ThreeGlyphs,vtkTypeBool);
  //@}

  //@{
  /**
   * Turn on/off drawing a mirror of each glyph
   */
  vtkSetMacro(Symmetric,vtkTypeBool);
  vtkGetMacro(Symmetric,vtkTypeBool);
  vtkBooleanMacro(Symmetric,vtkTypeBool);
  //@}

  //@{
  /**
   * Set/Get the distance, along x, from the origin to the end of the
   * source glyph. It is used to draw the symmetric glyphs.
   */
  vtkSetMacro(Length,G4double);
  vtkGetMacro(Length,G4double);
  //@}

  //@{
  /**
   * Turn on/off extraction of eigenvalues from tensor.
   */
  vtkSetMacro(ExtractEigenvalues,vtkTypeBool);
  vtkBooleanMacro(ExtractEigenvalues,vtkTypeBool);
  vtkGetMacro(ExtractEigenvalues,vtkTypeBool);
  //@}

  //@{
  /**
   * Turn on/off coloring of glyph with input scalar data or
   * eigenvalues. If false, or input scalar data not present, then the
   * scalars from the source object are passed through the filter.
   */
  vtkSetMacro(ColorGlyphs,vtkTypeBool);
  vtkGetMacro(ColorGlyphs,vtkTypeBool);
  vtkBooleanMacro(ColorGlyphs,vtkTypeBool);
  //@}

  enum
  {
      COLOR_BY_SCALARS,
      COLOR_BY_EIGENVALUES
  };

  //@{
  /**
   * Set the color mode to be used for the glyphs.  This can be set to
   * use the input scalars (default) or to use the eigenvalues at the
   * point.  If ThreeGlyphs is set and the eigenvalues are chosen for
   * coloring then each glyph is colored by the corresponding
   * eigenvalue and if not set the color corresponding to the largest
   * eigenvalue is chosen.  The recognized values are:
   * COLOR_BY_SCALARS = 0 (default)
   * COLOR_BY_EIGENVALUES = 1
   */
  vtkSetClampMacro(ColorMode, int, COLOR_BY_SCALARS, COLOR_BY_EIGENVALUES);
  vtkGetMacro(ColorMode, int);
  void SetColorModeToScalars()
    {this->SetColorMode(COLOR_BY_SCALARS);};
  void SetColorModeToEigenvalues()
    {this->SetColorMode(COLOR_BY_EIGENVALUES);};
  //@}

  //@{
  /**
   * Turn on/off scalar clamping. If scalar clamping is on, the ivar
   * MaxScaleFactor is used to control the maximum scale factor. (This is
   * useful to prevent uncontrolled scaling near singularities.)
   */
  vtkSetMacro(ClampScaling,vtkTypeBool);
  vtkGetMacro(ClampScaling,vtkTypeBool);
  vtkBooleanMacro(ClampScaling,vtkTypeBool);
  //@}

  //@{
  /**
   * Set/Get the maximum allowable scale factor. This value is compared to the
   * combination of the scale factor times the eigenvalue. If less, the scale
   * factor is reset to the MaxScaleFactor. The boolean ClampScaling has to
   * be "on" for this to work.
   */
  vtkSetMacro(MaxScaleFactor,G4double);
  vtkGetMacro(MaxScaleFactor,G4double);
  //@}

protected:
  vtkTensorGlyphColor();
  ~vtkTensorGlyphColor() override;

  int RequestUpdateExtent(vtkInformation *,  vtkInformationVector **, vtkInformationVector *) override;
  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
  int FillInputPortInformation(int port, vtkInformation *info) override;

  vtkTypeBool Scaling; // Determine whether scaling of geometry is performed
  G4double ScaleFactor; // Scale factor to use to scale geometry
  vtkTypeBool ExtractEigenvalues; // Boolean controls eigenfunction extraction
  vtkTypeBool ColorGlyphs; // Boolean controls coloring with input scalar data
  int ColorMode; // The coloring mode to use for the glyphs.
  vtkTypeBool ClampScaling; // Boolean controls whether scaling is clamped.
  G4double MaxScaleFactor; // Maximum scale factor (ScaleFactor*eigenvalue)
  vtkTypeBool ThreeGlyphs; // Boolean controls drawing 1 or 3 glyphs
  vtkTypeBool Symmetric; // Boolean controls drawing a "mirror" of each glyph
  G4double Length; // Distance, in x, from the origin to the end of the glyph
private:
  vtkTensorGlyphColor(const vtkTensorGlyphColor&) = delete;
  void operator=(const vtkTensorGlyphColor&) = delete;
};

#endif
