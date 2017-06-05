//
//  geometry.swift
//  PythagorasTree
//
//  Created by Lou Knauer on 05.06.17.
//
//

import Cocoa

extension CGVector {
    func length() -> CGFloat {
        return sqrt((self.dx * self.dx) + (self.dy * self.dy))
    }
    
    mutating func rotate(by angle: CGFloat) {
        let s = sin(angle)
        let c = cos(angle)
        let dx = self.dx * c - self.dy * s
        let dy = self.dx * s + self.dy * c
        self.dx = dx
        self.dy = dy
    }
    
    mutating func mul(_ x: CGFloat) {
        self.dx = self.dx * x
        self.dy = self.dy * x
    }
    
    static func from(A a: CGPoint, B b: CGPoint) -> CGVector {
        return CGVector(dx: b.x - a.x, dy: b.y - a.y)
    }
}

func += (lhs: inout CGPoint, rhs: CGVector) {
    lhs.x += rhs.dx
    lhs.y += rhs.dy
}

func + (lhs: CGPoint, rhs: CGVector) -> CGPoint {
    return CGPoint(x: lhs.x + rhs.dx, y: lhs.y + rhs.dy)
}

func -= (lhs: inout CGPoint, rhs: CGVector) {
    lhs.x -= rhs.dx
    lhs.y -= rhs.dy
}

func - (lhs: CGPoint, rhs: CGVector) -> CGPoint {
    return CGPoint(x: lhs.x - rhs.dx, y: lhs.y - rhs.dy)
}

struct Square {
    let origin: CGPoint
    let va: CGVector
    let vb: CGVector
    var top: CGPoint? = nil
    
    init(origin: CGPoint, va: CGVector, vb: CGVector) {
        self.origin = origin
        self.va = va
        self.vb = vb
    }
    
    mutating func calcTop(rotation: CGFloat) {
        let pos = CGPoint(x: origin.x + va.dx + (vb.dx / 2),
                          y: origin.y + va.dy + (vb.dy / 2))
        
        var vec = CGVector(dx: va.dx / 2, dy: va.dy / 2)
        vec.rotate(by: rotation)
        
        top = pos + vec
    }
    
    func getNextSquareToTheLeft() -> Square {
        return Square(origin: origin + va,
                      va: CGVector(dx: top!.x - (origin.x + va.dx + vb.dx),
                                   dy: top!.y - (origin.y + va.dy + vb.dy)),
                      vb: CGVector(dx: top!.x - (origin.x + va.dx),
                                   dy: top!.y - (origin.y + va.dy)))
    }
    
    func getNextSquareToTheRight() -> Square {
        return Square(origin: top!,
                      va: CGVector(dx: top!.x - (origin.x + va.dx),
                                   dy: top!.y - (origin.y + va.dy)),
                      vb: CGVector(dx: (origin.x + va.dx + vb.dx) - top!.x,
                                   dy: (origin.y + va.dy + vb.dy) - top!.y))
    }
    
    func draw(on canvas: NSImage, lineWidth: CGFloat) {
        let path = NSBezierPath()
        
        var pos = origin
        path.move(to: pos)
        pos += va
        path.line(to: pos)
        pos += vb
        path.line(to: pos)
        pos -= va
        path.line(to: pos)
        pos -= vb
        path.line(to: pos)
        
        path.lineWidth = lineWidth
        path.stroke()
    }
    
}


/*
struct Square {
    let origin: CGPoint // Unten links
    let vecA: CGVector  // von origin nach oben
    let vecB: CGVector  // von origin nach links
    let TM: CGPoint     // der punkt an dem sich die nächten Rechtecke berühren
    let TL: CGPoint     // oben links
    let TR: CGPoint     // oben rechts
    let BR: CGPoint     // unten rechts
    
    init(origin: CGPoint, vecA: CGVector, vecB: CGVector, rotation: CGFloat) {
        self.origin = origin
        self.vecA = vecA
        self.vecB = vecB
        self.TL = origin + vecA
        self.TR = origin + vecA + vecB
        self.BR = origin + vecB
        
        var TM = self.TL
        
        var vec = vecB
        vec.mul(0.5)
        TM += vec
        vec.rotate(by: rotation)
        
        self.TM = TM + vec
    }
    
    func getNextSquareToTheLeft(rotation: CGFloat) -> Square {
        return Square(origin: self.TL,
                      vecA: CGVector.from(A: self.TR, B: self.TM),
                      vecB: CGVector.from(A: self.TL, B: self.TM),
                      rotation: rotation)
    }
    
    func getNextSquareToTheRight(rotation: CGFloat) -> Square {
        return Square(origin: self.TM,
                      vecA: CGVector.from(A: self.TL, B: self.TM),
                      vecB: CGVector.from(A: self.TM, B: self.TR),
                      rotation: rotation)
    }
    
    func draw(on canvas: NSImage, lineWidth: CGFloat) {
        let path = NSBezierPath()
        
        path.move(to: self.origin)
        path.line(to: self.TL)
        path.line(to: self.TR)
        path.line(to: self.BR)
        path.line(to: self.origin)
        
        path.lineWidth = lineWidth
        path.stroke()
    }
}
*/
