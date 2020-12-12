#ifndef IMAGEPROCESSOR_VIEW_H
#define IMAGEPROCESSOR_VIEW_H

namespace image_processor::view {

class View {
  public:
    View() = default;
    virtual ~View() = default;

    virtual void Render() = 0;
    virtual auto WantClose() -> bool;

  protected:
    void SetWantClose();

  private:
    bool want_close_{false};
};

}  // namespace image_processor::view

#endif  // IMAGEPROCESSOR_VIEW_H
