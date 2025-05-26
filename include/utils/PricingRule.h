#ifndef _PRICING_STRATEGY_H_
#define _PRICING_STRATEGY_H_

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include "../utils/DatabaseManager.h"
#include "../models/Ticket.h"
#include "../models/User.h"
#include "../models/Seat.h"
using std::string;

/**
 * @struct TicketContext
 * @brief Context for pricing strategies, containing ticket, user, and seat information.
 */
struct TicketContext {
    Ticket ticket;   /**< Ticket information */
    User user;       /**< User information */
    Seat seat;       /**< Seat information */
};

/**
 * @class IPricingStrategy
 * @brief Interface for pricing strategies.
 *
 * Defines methods for checking applicability, applying the strategy, and getting priority.
 */
class IPricingStrategy {
private:
    int priority;
public:
    IPricingStrategy() = default;
    virtual ~IPricingStrategy() = default;
    /**
     * @brief Check if the strategy is applicable to the given context.
     * @param ctx TicketContext
     * @return True if applicable, false otherwise
     */
    virtual bool isApplicable(const TicketContext& ctx) = 0;
    /**
     * @brief Apply the pricing strategy to the base price.
     * @param basePrice The original price
     * @return The price after applying the strategy
     */
    virtual double apply(double basePrice) = 0;
    /**
     * @brief Get the priority of the strategy.
     * @return Priority as an integer
     */
    virtual int getPriority() const = 0;
};

/**
 * @class StudentDiscountStrategy
 * @brief Pricing strategy for student discount.
 *
 * Applies a discount if the user's email contains "@student".
 */
class StudentDiscountStrategy : public IPricingStrategy {
private:
    int priority = 0;  // Độ ưu tiên của chiến lược
public:
    bool isApplicable(const TicketContext& ctx) override {
        string email = ctx.user.getEmail();
        // Kiểm tra nếu email chứa "@student"
        if (email.find("@student") != string::npos) { 
           return true;  // Nếu là sinh viên
        }
        return false;  // Nếu không phải sinh viên
    }
    double apply(double basePrice) override {
        return std::max(0.0, basePrice - 20000);
    }
    int getPriority() const override {
        return priority;  // Trả về độ ưu tiên
    }
};

/**
 * @class VipSeatStrategy
 * @brief Pricing strategy for VIP seats.
 *
 * Adds a surcharge if the seat is VIP.
 */
class VipSeatStrategy : public IPricingStrategy {
private:
    int priority = 1;  // Độ ưu tiên của chiến lược
public:
    bool isApplicable(const TicketContext& ctx) override {
        return ctx.seat.isVip();  // Kiểm tra nếu ghế là ghế VIP
    }
    double apply(double basePrice) override {
        return basePrice + 20000;  // Thêm 20k cho ghế VIP
    }
    int getPriority() const override {
        return priority;  // Trả về độ ưu tiên
    }
};

/**
 * @class EveningShowStrategy
 * @brief Pricing strategy for evening showtimes.
 *
 * Increases price for showtimes between 18:00 and 24:00.
 */
class EveningShowStrategy : public IPricingStrategy {
private:
    int priority = 2;  // Độ ưu tiên của chiến lược
public:
    bool isApplicable(const TicketContext& ctx) override {
        // Kiểm tra nếu thời gian chiếu là buổi tối
        std::string showTime = ctx.ticket.getShowTime();
        // tính toán thời gian từ chuỗi dạng YYYY-MM-DD HH:MM:SS
        int hour = std::stoi(showTime.substr(11, 2));
        return (hour >= 18 && hour < 24);  // Giả sử buổi tối là từ 18h đến 24h
    }
    double apply(double basePrice) override {
        return basePrice * 1.05;  // Tăng giá cho buổi tối
    }
    int getPriority() const override {
        return priority;  // Trả về độ ưu tiên
    }
};

/**
 * @class HolidayStrategy
 * @brief Pricing strategy for holidays.
 *
 * Increases price for specific holiday dates.
 */
class HolidayStrategy : public IPricingStrategy {
private:
    int priority = 3;  // Độ ưu tiên của chiến lược
public:
    bool isApplicable(const TicketContext& ctx) override {
        // Kiểm tra nếu ngày chiếu là ngày lễ
        std::string showTime = ctx.ticket.getShowTime();
        // Giả sử ngày lễ là 1 tháng 1, 30/4, 1/5, 2/9, 25/12
        if (showTime.substr(5, 2) == "09" && showTime.substr(8, 2) == "02") { 
            return true;
        }
        if (showTime.substr(5, 2) == "12" && showTime.substr(8, 2) == "25") {
            return true;
        }
        if (showTime.substr(5, 2) == "01" && showTime.substr(8, 2) == "01") {
            return true;
        }
        if (showTime.substr(5, 2) == "04" && showTime.substr(8, 2) == "30") {
            return true;
        }
        if (showTime.substr(5, 2) == "05" && showTime.substr(8, 2) == "01") {
            return true;
        }
        return false;
    }
    double apply(double basePrice) override {
        return basePrice * 1.10;  // Tăng giá cho ngày lễ
    }
    int getPriority() const override {
        return priority;  // Trả về độ ưu tiên
    }
};

/**
 * @class PricingStrategyFactory
 * @brief Factory for creating pricing strategies by name.
 */
class PricingStrategyFactory {
private:
    std::map<std::string, std::shared_ptr<IPricingStrategy>> strategies;
public:
    PricingStrategyFactory() {
        strategies["StudentDiscount"] = std::make_shared<StudentDiscountStrategy>();
        strategies["VipSeat"] = std::make_shared<VipSeatStrategy>();
        strategies["EveningShow"] = std::make_shared<EveningShowStrategy>();
        strategies["Holiday"] = std::make_shared<HolidayStrategy>();
    }

    /**
     * @brief Get a pricing strategy by name.
     * @param strategyName Name of the strategy
     * @return Shared pointer to the strategy, or nullptr if not found
     */
    std::shared_ptr<IPricingStrategy> getStrategy(const std::string& strategyName) {
        if (strategies.find(strategyName) != strategies.end()) {
            return strategies[strategyName];
        }
        return nullptr;
    }
};

/**
 * @class PricingContext
 * @brief Context for managing and applying multiple pricing strategies.
 */
class PricingContext {
private:
    std::vector<std::shared_ptr<IPricingStrategy>> strategies;
public:
    /**
     * @brief Add a pricing strategy to the context.
     * @param strategy Shared pointer to the strategy
     */
    void addStrategy(std::shared_ptr<IPricingStrategy> strategy) {
        strategies.push_back(strategy);
    }

    /**
     * @brief Calculate the final price by applying all applicable strategies in priority order.
     * @param ctx TicketContext
     * @return Final ticket price
     */
    double calculatePrice(const TicketContext& ctx) {
        // sắp xếp các chiến lược theo độ ưu tiên tăng dần
        std::sort(strategies.begin(), strategies.end(),
        [](const std::shared_ptr<IPricingStrategy>& a, const std::shared_ptr<IPricingStrategy>& b) {
            return a->getPriority() < b->getPriority();
        });
        double basePrice = ctx.ticket.getPrice();
        for (const auto& strategy : strategies) {
            if (strategy->isApplicable(ctx)) {
                basePrice = strategy->apply(basePrice);
            }
        }
        return basePrice;
    }

    /**
     * @brief Remove all strategies from the context.
     */
    void clearStrategies() {
        strategies.clear();
    }

    /**
     * @brief Load active pricing strategies from the database.
     *
     * Queries the database for active rules and adds corresponding strategies.
     */
    void loadStrategiesFromDatabase() {
        // tìm các quy tắc trong cơ sở dữ có active = true
        string query = "SELECT ruleName FROM PricingRule where isActive = true";
        QueryResult result = DatabaseManager::getInstance()->executeQuery(query);
        if (result.success) {
            MYSQL_RES* res = result.result.get();
            MYSQL_ROW row;

            PricingStrategyFactory factory;
            while ((row = mysql_fetch_row(res))) {
                std::string ruleName = row[0];
                std::shared_ptr<IPricingStrategy> strategy  = factory.getStrategy(ruleName);
                if (strategy) {
                    addStrategy(strategy);
                }
            }
        } else {
            std::cerr << "Error loading strategies from database: " << result.error_message << std::endl;
        }
    }
};

#endif