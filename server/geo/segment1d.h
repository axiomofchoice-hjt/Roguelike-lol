#pragma once

namespace geo {
/// 区间
struct segment1d {
    /// 区间左端点
    float l;
    /// 区间右端点
    float r;
    segment1d(float p1, float p2);
};

/// 区间移动
inline segment1d move(segment1d s, float f) {
    return segment1d(s.l + f, s.r + f);
}

/// 判定区间包含实数（含端点）
bool is_contain(segment1d s, float f);

/// 两个区间相交 / 有重叠部分
bool is_intersect(segment1d s1, segment1d s2);
}  // namespace geo