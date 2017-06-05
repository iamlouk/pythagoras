
import Cocoa

let contentRect = CGRect(x: 0, y: 0, width: 900, height: 600)
let window = NSWindow(contentRect: contentRect,
                      styleMask: NSTitledWindowMask,
                      backing: NSBackingStoreType.buffered,
                      defer: true)

window.makeKeyAndOrderFront(nil)
window.backgroundColor = NSColor.black
window.title = "Pythagoras (^C to quit)"

var canvas: NSImage
let view: NSImageView

var x: CGFloat = 0

let depth = 10
let lineWidth: CGFloat = 1
let startWidth = 125
let startSquare: Square = Square(origin: CGPoint(x: CGFloat(contentRect.width / 2 - CGFloat(startWidth / 2)),
                                                 y: 0),
                                 va: CGVector(dx: 0, dy: startWidth),
                                 vb: CGVector(dx: startWidth, dy: 0))

view = NSImageView(frame: contentRect)
window.contentView = view
canvas = NSImage(size: contentRect.size)

func drawRecurive(square: Square, counter: Int, angle: CGFloat) {
    square.draw(on: canvas, lineWidth: lineWidth)
    if counter > 0 {
        var square = square
        square.calcTop(rotation: angle)
        drawRecurive(square: square.getNextSquareToTheLeft(),
                     counter: counter - 1,
                     angle: angle)
        
        drawRecurive(square: square.getNextSquareToTheRight(),
                     counter: counter - 1,
                     angle: angle)
    }
}

func render() {
    let angle: CGFloat = sin(x) * 0.1
    
    x += 0.005
    
    canvas = NSImage(size: contentRect.size)
    view.image = canvas
    
    canvas.lockFocus()
    NSColor.green.set()
    
    drawRecurive(square: startSquare, counter: depth, angle: angle)
    
    canvas.unlockFocus()
    
}

if #available(OSX 10.12, *) {
    var timer: Timer = Timer.scheduledTimer(withTimeInterval: 1000 / (25 * 1000),
                                            repeats: true,
                                            block: {_ in render() })

} else {
    // Fallback on earlier versions
    print("only available in OSX 10.12 or newer")
    exit(1)
}

RunLoop.main.run()
