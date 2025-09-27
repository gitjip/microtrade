#include "product.h"

Product::Product() {}

QString Product::id() const { return m_id; }

QString Product::name() const { return m_name; }

QString Product::description() const { return m_description; }

double Product::price() const { return m_price; }

qint64 Product::stock() const { return m_stock; }

Product::Category Product::category() const { return m_category; }

QUrl Product::imageUrl() const { return m_imageUrl; }

QDateTime Product::listedAt() const { return m_listedAt; }

QDateTime Product::delistedAt() const { return m_delistedAt; }

bool Product::isDeleted() const { return m_isDeleted; }
