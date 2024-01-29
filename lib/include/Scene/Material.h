


#ifndef PLUTONIUM_MATERIAL_H
#define PLUTONIUM_MATERIAL_H


#include "Shape.h"
#include "Color.h"


class Ray;


class Material {
public:

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const = 0;
    virtual Color emit() const {return Color(0.0, 0.0, 0.0);}

private:

};



class Lambert : public Material {
public:

    Lambert(const Color& albedo_) : albedo(albedo_) {}

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:

    Color albedo;

};


class Metal : public Material {
public:

    Metal(const Color& albedo_, float roughness_) : albedo(albedo_) { if(roughness_ < 1.0) roughness = roughness_; else roughness = 1.0; }

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:

    Color albedo;
    float roughness;

};


class Dielectric : public Material {
public:

    Dielectric(float refractionIndex_) : refractionIndex(refractionIndex_) {}

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;

private:

    float schlick(float cosine, float refractionIndex) const;

    float refractionIndex;

};



class DiffuseLight : public Material {
public:

    DiffuseLight(const Color& emittedColor_) : emittedColor(emittedColor_) {}

    virtual bool scatter(const Ray& rIn, const HitRecord& rec, Color& attenuation, Ray& scattered) const override;
    virtual Color emit() const override;

private:

    Color emittedColor;

};





#endif